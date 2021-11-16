#pragma once
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( NORMAL_BLOCK , __FILE_ , _LINE_ )
#define new DBG_NEW
#endif
#endif