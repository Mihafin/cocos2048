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
        {2,     Color4F(0xee/255.0f, 0xe4/255.0f, 0xda/255.0f, 1.0f)},
        {4,     Color4F(0xed/255.0f, 0xe0/255.0f, 0xc8/255.0f, 1.0f)},
        {8,     Color4F(0xf2/255.0f, 0xb1/255.0f, 0x79/255.0f, 1.0f)},
        {16,    Color4F(0xf5/255.0f, 0x95/255.0f, 0x63/255.0f, 1.0f)},
        {32,    Color4F(0xf6/255.0f, 0x7c/255.0f, 0x5f/255.0f, 1.0f)},
        {64,    Color4F(0xf6/255.0f, 0x5e/255.0f, 0x3b/255.0f, 1.0f)},
        {128,   Color4F(0xed/255.0f, 0xcf/255.0f, 0x72/255.0f, 1.0f)},
        {256,   Color4F(0xed/255.0f, 0xcc/255.0f, 0x61/255.0f, 1.0f)},
        {512,   Color4F(0xed/255.0f, 0xc8/255.0f, 0x50/255.0f, 1.0f)},
        {1024,  Color4F(0xed/255.0f, 0xc5/255.0f, 0x3f/255.0f, 1.0f)},
        {2048,  Color4F(0xed/255.0f, 0xc2/255.0f, 0x2e/255.0f, 1.0f)}
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
