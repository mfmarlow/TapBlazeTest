#include "LiveTextField.h"

LiveTextField::LiveTextField(string new_label_text, Node* new_parent, Vec2 new_position, int new_live_var, int new_tag)
{
	label_text = new_label_text;
	parent = new_parent;
	position = new_position;
	live_var = new_live_var;
	tag = new_tag;
	label = nullptr;
	field = nullptr;
}

LiveTextField* LiveTextField::createWith(string new_label_text, Node* new_parent, Vec2 new_position, int new_live_var, int new_tag)
{
	auto ret = new (std::nothrow) LiveTextField(new_label_text, new_parent, new_position, new_live_var, new_tag);

	if (ret)
	{
		//create label
		auto label = Label::createWithSystemFont(ret->label_text, "Arial", 20);
		label->setPosition(ret->position);
		ret->parent->addChild(label, 1);
		ret->setLabel(label);

		//create textflied
		auto field = TextField::create(to_string(ret->live_var), "Arial", 20);
		ret->parent->addChild(field, 1);
		field->setPosition(Vec2(ret->position.x*1.75, ret->position.y));
		field->setMaxLengthEnabled(true);
		field->setMaxLength(3);
		field->setTag(ret->tag);
		ret->setField(field);
		return ret;
	}

	return nullptr;
}

Label* LiveTextField::getLabel()
{
	return label;
}

TextField* LiveTextField::getTextField()
{
	return field;
}

void LiveTextField::setField(TextField* new_field)
{
	field = new_field;
}

void LiveTextField::setLabel(Label* new_label)
{
	label = new_label;
}
