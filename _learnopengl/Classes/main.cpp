#include <main.h>

int testPart();
int demoTestFunc();

int main()
{
    testPart();
    return 0;
}

int demoTestFunc() {
    return 0;
}

int testPart()
{
    // start
    //ModelLoad::enter();
    //Color::enter();
    //Coord::enter();
    //Transform::enter();
    //Texture::enter();
    //HelloTriangle::enter();

    // advanced
    //DepthTest::enter();
    //StencilTest::enter();
    //DiscardFrag::enter();
    //BlendTest::enter();
    FrameBuffer::enter();

    return 0;
}