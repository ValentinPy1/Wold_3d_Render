/*
** EPITECH PROJECT, 2021
** world
** File description:
** redim.c
*/

#include "my_world.h"

int input_num(winbase_t *wb)
{
    if (sfKeyNum0 <= wb->event.key.code && wb->event.key.code <= sfKeyNum9) {
        return wb->event.key.code - sfKeyNum0;
    } else if (sfKeyEnter == wb->event.key.code) {
        return -2;
    } else {
        return -1;
    }
}

void spe_event(winbase_t *wb, char *text, int *i)
{
    int my_char;
    while (sfRenderWindow_pollEvent(wb->window, &wb->event)) {
        switch (wb->event.type) {
            case (sfEvtClosed):
                sfRenderWindow_close(wb->window);
                break;
            case (sfEvtKeyPressed):
                my_char = input_num(wb);
                if (my_char >= 0) {
                    text[*i] = my_char + '0';
                    *i += 1;
                    text[*i] = 0;
                }
                if (my_char == -2 || *i > 4) {
                    *i = -1;
                    return;
                }
                break;
            default:
                break;
        }
    }
}

char *get_redim_text(winbase_t *wb)
{
    sfVector2f **projmap;
    char *text = malloc(5);
    text[0] = 0;
    int i = 0;
    while (sfRenderWindow_isOpen(wb->window)) {
        spe_event(wb, text, &i);
        if (i == -1)
            break;
        projmap = project_map(wb);
        draw_all(wb, projmap, text);
        destroy_projmap(&wb->world.dim, projmap);
    }
    return text;
}

void redim_trigger(winbase_t *wb)
{
    char *str_x = get_redim_text(wb);
    char *str_y = get_redim_text(wb);
    int x = atoi(str_x);
    int y = atoi(str_y);
    wb->world.dim = (sfVector2i){x, y};
    free(wb->height_map);
    wb->height_map = setup_map(x, y);
    free(str_x);
    free(str_y);
}