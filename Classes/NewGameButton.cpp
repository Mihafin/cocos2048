#include "NewGameButton.hpp"
#include "RoundedRect.hpp"

USING_NS_CC;

NS_GAME_BEGIN
//todo: сделать универсальный класс
bool NewGameButton::init()
{
    if (!DrawNode::init()){
        return false;
    }
    
    auto btnW = 200, btnH = 60, fntSize = 35;

    auto back = RoundedRect::create();
    back->setPosition(Vec2::ZERO);
    back->setSizeAndColor(Vec2(btnW, btnH), Color4F(0x8f/255.0f, 0x7a/255.0f, 0x66/255.0f, 1.0f));
    
    auto btnText = Label::createWithTTF(Consts::newGameText, Consts::guiFont, fntSize);
    btnText->setTextColor(Color4B(0xf9, 0xf6, 0xf2, 255));
    btnText->setPosition(Vec2(btnW/2, btnH/2));
    
    addChild(back);
    addChild(btnText);
    
    setContentSize(Size(btnW, btnH));
    return true;
}

NS_GAME_END
