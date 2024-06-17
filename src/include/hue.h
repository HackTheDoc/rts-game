#pragma once

#include <SDL2/SDL.h>

namespace hue {
    const SDL_Color invisible               = {   0,   0,   0,   0 };

    const SDL_Color black                   = {   0,   0,   0, 255 };
    const SDL_Color white                   = { 255, 255, 255, 255 };
    const SDL_Color red                     = { 255,  85,  85, 255 }; // #ff5555
    const SDL_Color blue                    = { 139, 233, 253, 255 }; // #8be9fd
    const SDL_Color green                   = {  80, 250, 123, 255 }; // #50fa7b
    const SDL_Color yellow                  = { 241, 250, 140, 255 }; // #f1fa8c

    const SDL_Color blur                    = {  40,  42,  54, 192 }; // #282a36
    const SDL_Color blur_yellow             = { 241, 250, 140, 128 }; // #f1fa8c
    const SDL_Color blur_white              = { 248, 248, 242, 192 }; // #f8f8f2

    const SDL_Color font                    = { 248, 248, 242, 255 }; // #f8f8f2
    const SDL_Color border                  = { 248, 248, 242, 255 }; // #f8f8f2

    const SDL_Color background              = {  22,  23,  29, 255 }; // #16171d

    const SDL_Color water                   = {  71, 171, 169, 255 }; // #47ABA9

    const SDL_Color card_background         = {  40,  42,  54, 255 }; // #282a36
    const SDL_Color card_border = border;
};
