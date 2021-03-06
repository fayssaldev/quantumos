#include "Basic/FileGroup.h"
#include "DisplayPrivate.h"
#include "BSP/BSP.h"

#if( XC_USE_LUA == 1)
#include "LuaInterface/LuaScript.h"
#endif

static lv_obj_t * appWindow;

static void Create_Luainput(lv_obj_t * parent);
static void Create_Luaoutput(lv_obj_t * parent);
static void TextAreaEvent_Handler(lv_obj_t * text_area, lv_event_t event);
static void KeyboardEvent_Handler(lv_obj_t * kb, lv_event_t event);

static lv_obj_t * ta_input;
static lv_obj_t * ta_output;
static lv_obj_t * tv;
static lv_obj_t * keyboard;
static lv_obj_t * tab_input;
static lv_obj_t * tab_output;

static void PageCreat_LuaScript()
{   
    tv = lv_tabview_create(appWindow, NULL);
    lv_obj_align(tv, appWindow, LV_ALIGN_IN_TOP_MID, 0, 0);
    lv_obj_set_size(tv, APP_WIN_WIDTH, APP_WIN_HEIGHT);

    tab_input = lv_tabview_add_tab(tv, LV_SYMBOL_EDIT);
    tab_output = lv_tabview_add_tab(tv, LV_SYMBOL_UPLOAD);

    Create_Luainput(tab_input);
    Create_Luaoutput(tab_output);
}

static const char *luaCode = "";

void LuaCodeSet(const char* code)
{
    luaCode = code;
}

static void Create_Luainput(lv_obj_t * parent)
{
    lv_page_set_style(parent, LV_PAGE_STYLE_BG, &lv_style_transp_fit);
    lv_page_set_style(parent, LV_PAGE_STYLE_SCRL, &lv_style_transp_fit);

    lv_page_set_sb_mode(parent, LV_SB_MODE_DRAG);

    /*text area*/
    ta_input = lv_ta_create(parent, NULL);
    lv_obj_set_size(ta_input, lv_page_get_scrl_width(parent), lv_obj_get_height(parent));
    lv_obj_set_event_cb(ta_input, TextAreaEvent_Handler);
    lv_ta_set_text(ta_input, luaCode);
#if( XC_USE_LUA == 1 )
    lv_ta_set_placeholder_text(ta_input, "No code...");
#else
    lv_ta_set_placeholder_text(ta_input, "Lua is not ready...");
#endif
}

static void Create_Luaoutput(lv_obj_t * parent)
{
    lv_page_set_style(parent, LV_PAGE_STYLE_BG, &lv_style_transp_fit);
    lv_page_set_style(parent, LV_PAGE_STYLE_SCRL, &lv_style_transp_fit);

    lv_page_set_sb_mode(parent, LV_SB_MODE_DRAG);

    /*text area*/
    ta_output = lv_ta_create(parent, NULL);
    lv_obj_set_size(ta_output, lv_page_get_scrl_width(parent), lv_obj_get_height(parent));
    lv_obj_set_event_cb(ta_output, TextAreaEvent_Handler);
    lv_ta_set_cursor_type(ta_output, LV_CURSOR_NONE);   
    lv_ta_set_text(ta_output, "");
}

static void TextAreaEvent_Handler(lv_obj_t * text_area, lv_event_t event)
{
    /*Text area is on the scrollable part of the page but we need the page itself*/
    lv_obj_t * parent = lv_obj_get_parent(lv_obj_get_parent(ta_input));

    if(event == LV_EVENT_CLICKED)
    {
        if(text_area == ta_input && !keyboard)
        {
            Keyboard_Activate(&keyboard, true, parent, ta_input, KeyboardEvent_Handler);
            static lv_anim_t a;
            lv_obj_add_anim(
                ta_input, &a,
                (lv_anim_exec_xcb_t)lv_obj_set_height,
                lv_obj_get_height(ta_input),  lv_obj_get_height(tab_input) - lv_obj_get_height(keyboard),
                500
            );
        }
    }
    else if(event == LV_EVENT_LONG_PRESSED)
    {
        if(text_area == ta_output)
        {
            lv_ta_set_text(ta_output, "");
        }
    }
}

#if( XC_USE_LUA == 1 )
static void LuaPrintCallback(const char* s)
{
    if(!ta_output)
        return;
    
    lv_ta_add_text(ta_output, s);
    
    if(lv_ta_get_cursor_pos(ta_output) > 200)
    {
        lv_ta_set_text(ta_output, "");
    }
}
#endif

/**
 * Called when the close or ok button is pressed on the keyboard
 * @param keyboard pointer to the keyboard
 * @return
 */
static void KeyboardEvent_Handler(lv_obj_t * kb, lv_event_t event)
{
    lv_kb_def_event_cb(kb, event);
    const char * txt = lv_btnm_get_active_btn_text(kb);
    
    if(event == LV_EVENT_PRESSED)
    {
        Motor_Vibrate(1.0f, 20);
    }
    
    if(event == LV_EVENT_LONG_PRESSED_REPEAT)
    {
        if(strcmp(txt, "Bksp") == 0)
        {
            lv_ta_set_text(ta_input, "");
        }
    }
    
    if(event == LV_EVENT_APPLY)
    {
#if( XC_USE_LUA == 1 )
        luaScript.registerStrOutput(LuaPrintCallback);
        LuaScriptStart(lv_ta_get_text(ta_input));
#endif
        lv_tabview_set_tab_act(tv, 1, true);
        lv_ta_add_text(ta_output, "\n> ");
    }
    
    if(event == LV_EVENT_CANCEL)
    {
#if( XC_USE_LUA == 1 )
        luaScript.end();
#endif
        Keyboard_Activate(&keyboard, false, NULL, NULL, NULL);
        lv_obj_set_height(ta_input, lv_obj_get_height(tab_input));
    }
    
    if(event == LV_EVENT_DELETE)
    {
        keyboard = NULL;
    }
}

/**
  * @brief  ??????????????
  * @param  ??
  * @retval ??
  */
static void Setup()
{
    lv_obj_move_foreground(appWindow);
    __ExecuteOnce(PageCreat_LuaScript());
    lv_obj_set_hidden(tv, false);
    lv_ta_set_text(ta_input, luaCode);
}

/**
  * @brief  ????????????
  * @param  ??
  * @retval ??
  */
static void Exit()
{
#if( XC_USE_LUA == 1 )
    luaScript.end();
#endif
    lv_obj_set_hidden(tv, true);
}

/**
  * @brief  ????????
  * @param  event:????????
  * @param  param:????????
  * @retval ??
  */
static void Event(int event, void* param)
{
    lv_obj_t * btn = (lv_obj_t*)param;
    if(event == LV_EVENT_CLICKED)
    {
        if(btn == btnBack)
        {
            if(keyboard)
            {
                lv_event_send(keyboard, LV_EVENT_CANCEL, NULL);
            }
            else
            {
                page.PagePop();
            }
        }
    }
}

/**
  * @brief  ????????
  * @param  pageID:??????????????ID??
  * @retval ??
  */
void PageRegister_LuaScript(uint8_t pageID)
{
    appWindow = AppWindow_GetCont(pageID);
    page.PageRegister(pageID, Setup, NULL, Exit, Event);
}

