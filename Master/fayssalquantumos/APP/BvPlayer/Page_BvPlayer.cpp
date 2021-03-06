#include "Basic/FileGroup.h"
#include "DisplayPrivate.h"
#include "BV_Player/BV_Player.h"
#include "BSP/BSP.h"

static lv_obj_t * appWindow;

static uint8_t* BvBuffer;
static BV_Player* BvPlayer;
static lv_task_t * taskBvPlayer;

static String BvFilePath;
void Bv_OpenFile(const char* path)
{
    BvFilePath = String(path);
    page.PagePush(PAGE_BvPlayer);
}

static void Screen_FastDrawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h)
{
    screen.drawFastRGBBitmap(x, y, bitmap, w, h);
}

static void Screen_FastDrawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h)
{
    screen.drawFastBitmap(x, y, bitmap, w, h);
}

static void Task_BvPlyaerUpdate(lv_task_t * task)
{
    BvPlayer->UpdatePlayerState();
    if(BvPlayer->IsEnd())
    {
        page.PagePop();
    }
}

/**
  * @brief  页面初始化事件
  * @param  无
  * @retval 无
  */
static void Setup()
{
    lv_obj_move_foreground(appWindow);
    taskBvPlayer = lv_task_create(Task_BvPlyaerUpdate, 33, LV_TASK_PRIO_MID, 0);
    uint32_t buffSize = MemPool_GetResidueSize();
    BvBuffer = (uint8_t*)MemPool_Malloc(buffSize);
    memset(BvBuffer, 0, buffSize);
    BvPlayer = new BV_Player(BvBuffer, buffSize);
    if(!BvPlayer->OpenVideo(BvFilePath))
    {
        return;
    }
    BvPlayer->BaseX = (APP_WIN_WIDTH - BvPlayer->Head.Width) * 0.5f;
    BvPlayer->BaseY = (APP_WIN_HEIGHT - BvPlayer->Head.Height) * 0.5f + BarStatus_GetHeight();
    BvPlayer->SetPlayerState(BvPlayer->Run);
    BvPlayer->DrawPic_16bit = Screen_FastDrawRGBBitmap;
    BvPlayer->DrawPic_8bit = Screen_FastDrawBitmap;
}

/**
  * @brief  页面退出事件
  * @param  无
  * @retval 无
  */
static void Exit()
{
    MemPool_Free(BvBuffer);
    BvPlayer->CloseVideo();
    delete BvPlayer;
    lv_task_del(taskBvPlayer);
}

/**
  * @brief  页面事件
  * @param  event:事件编号
  * @param  param:事件参数
  * @retval 无
  */
static void Event(int event, void* param)
{
    lv_obj_t * btn = (lv_obj_t*)param;
    if(event == LV_EVENT_CLICKED)
    {
        if(btn == btnBack)
        {
            page.PagePop();
        }
    }
}

/**
  * @brief  页面注册
  * @param  pageID:为此页面分配的ID号
  * @retval 无
  */
void PageRegister_BvPlayer(uint8_t pageID)
{
    appWindow = AppWindow_GetCont(pageID);
    lv_style_t * style = (lv_style_t *)lv_cont_get_style(appWindow, LV_CONT_STYLE_MAIN);
    *style = lv_style_pretty;
    page.PageRegister(pageID, Setup, NULL, Exit, Event);
}
