#pragma once

#include "graphics.h"
#include "stdfunc.h"

void kernel(FrameBuffer *FrameBuffer);
extern "C" void kernel_start(FrameBuffer *FrameBuffer);