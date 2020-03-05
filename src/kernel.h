#pragma once

#include "graphics.h"
#include "stdfunc.h"

extern "C" void kernel_start(FrameBuffer *FrameBuffer);
void kernel(FrameBuffer *FrameBuffer);