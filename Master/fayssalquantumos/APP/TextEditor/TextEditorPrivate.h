#ifndef __TEXTEDITOR_PRIVATE_H
#define __TEXTEDITOR_PRIVATE_H

#include "SdFat.h"

void TextEditorSet(char* text, SdFile file);
bool TextEditorGetLocked();

#define TextBuffSize (5 * 1024)

#endif
