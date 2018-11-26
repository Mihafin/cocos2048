#include "Cell.hpp"
#include "Constants.h"
#include "cocos2d.h"
#include "RoundedRect.hpp"

USING_NS_CC;

NS_GAME_BEGIN
bool Cell::init(){
    if (!DrawNode::init()){
        return false;
    }

    _back = RoundedRect::create();
    _back->setPosition(Vec2(-WIDTH/2, -HEIGHT/2));
    _lblVal = Label::createWithTTF("", Consts::gameFont, getFontSize());
    
    addChild(_back, -1);
    addChild(_lblVal, 1);
    
    setScale(0);
    return true;
}

float Cell::getFontSize() {
    return _val < 100 ? 60 : (_val < 1000 ? 50 : 40); // todo: move to consts or calculate
}

Color4F Cell::getFillColor(){
    static std::unordered_map<int, Color4F> colors {
        {2,     Color4F(0xee/250.0f, 0xe4/250.0f, 0xda/250.0f, 1.0f)},
        {4,     Color4F(0xed/250.0f, 0xe0/250.0f, 0xc8/250.0f, 1.0f)},
        {8,     Color4F(0xf2/250.0f, 0xb1/250.0f, 0x79/250.0f, 1.0f)},
        {16,    Color4F(0xf5/250.0f, 0x95/250.0f, 0x63/250.0f, 1.0f)},
        {32,    Color4F(0xf6/250.0f, 0x7c/250.0f, 0x5f/250.0f, 1.0f)},
        {64,    Color4F(0xf6/250.0f, 0x5e/250.0f, 0x3b/250.0f, 1.0f)},
        {128,   Color4F(0xed/250.0f, 0xcf/250.0f, 0x72/250.0f, 1.0f)},
        {256,   Color4F(0xed/250.0f, 0xcc/250.0f, 0x61/250.0f, 1.0f)},
        {512,   Color4F(0xed/250.0f, 0xc8/250.0f, 0x50/250.0f, 1.0f)},
        {1024,  Color4F(0xed/250.0f, 0xc5/250.0f, 0x3f/250.0f, 1.0f)},
        {2048,  Color4F(0xed/250.0f, 0xc2/250.0f, 0x2e/250.0f, 1.0f)}
    };
    return colors[_val];
}

Color4B Cell::getTextColor() {
    return _val > 4 ? Color4B(0xf9, 0xf6, 0xf2, 255) : Color4B(0x77, 0x6e, 0x65, 255);
}

void Cell::show(int val){
    _val = val;
    
    _lblVal->setString(std::to_string(_val));
    _lblVal->setTextColor(getTextColor());
    _lblVal->setSystemFontSize(getFontSize());
    
    auto sacelAction = ScaleTo::create(Consts::APEAR_TIME, 1.0f);
    auto seq = Sequence::create(DelayTime::create(Consts::APEAR_TIME), sacelAction, nullptr);
    seq->setTag((int)Consts::ActionTag::Scale);
    runAction(seq);
    
    _back->setSizeAndColor(Vec2(WIDTH, HEIGHT), getFillColor());
}

void Cell::up(int newVal){
    _val = newVal;
    
    _lblVal->setString(std::to_string(_val));
    _lblVal->setTextColor(getTextColor());
    _lblVal->setSystemFontSize(getFontSize());
    
    stopAllActionsByTag((int)Consts::ActionTag::Scale);
    auto scaleMax = ScaleTo::create(Consts::MOVE_TIME, 1.2f);
    auto scaleNorm = ScaleTo::create(Consts::MOVE_TIME, 1.0f);
    auto seq = Sequence::create(scaleMax, scaleNorm, nullptr);
    seq->setTag((int)Consts::ActionTag::Scale);
    runAction(seq);
    
    _back->setSizeAndColor(Vec2(WIDTH, HEIGHT), getFillColor());
}

void Cell::win(){
    //todo: some beautifull
}

void Cell::setHistory(std::string& mes) {
    _hist.append(mes);
}

std::string& Cell::getHistory(){
    return _hist;
}

int Cell::val(){
    return _val;
}

NS_GAME_END
