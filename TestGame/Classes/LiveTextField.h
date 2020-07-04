#pragma once

#ifndef __LIVE_TEXT_FIELD_H__
#define __LIVE_TEXT_FIELD_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
USING_NS_CC;
using namespace ui;

//custom UI element that contains a label and a textfield
class LiveTextField
{
public:
    LiveTextField(string label_text, Node* parent, Vec2 position, int live_var, int tag);
    TextField* getTextField();
    Label* getLabel();
    void setLabel(Label* new_label);
    void setField(TextField* new_field);
    static LiveTextField* createWith(string label_text, Node* parent, Vec2 position, int live_var, int tag);
private:
    Label* label;
    string label_text;
    TextField* field;
    Node* parent;
    Vec2 position;
    int live_var;
    int tag;
};

#endif // __LIVE_TEXT_FIELD_H__