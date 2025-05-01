// /*
// ** EPITECH PROJECT, 2025
// ** header
// ** File description:
// ** header
// */

// #include "corewar.h"
// #include "parsing.h"
// #include <stddef.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>

// static int analyse_instructions(
//     parsing_data_t *parse_data,
//     FILE *fptr,
//     int prog_size)
// {
//     int i = 0;
//     int inst_idx = 0;
//     char buffer[prog_size + 1];

//     fseek(fptr, 1, prog_size);
//     fread(buffer, (size_t)prog_size, 1, fptr);
//     while (i < prog_size) {
//         parse_data->instruction[inst_idx] = my_malloc(sizeof(instruction_t));
//         parse_data->instruction[inst_idx]->op_code = (u_int8_t)buffer[i];
//         parse_data->instruction[inst_idx]->coding_byte =
//             (u_int8_t)buffer[i + 1];
//         i += verify_coding_byte(parse_data->instruction[inst_idx]);
//         i += parse_params(parse_data->instruction[inst_idx], &buffer[i]);
//         inst_idx++;
//     }
//     return 1;
// }

// int parse_champions(
//     parsing_data_t *parse_data,
//     program_data_t *program_data)
// {
//     FILE *fptr = fopen(program_data->filename, "r");
//     header_t *header = my_calloc(1, sizeof(header_t));

//     fread(header, sizeof(header_t), 1, fptr);
//     header->prog_size = (int)swap_endian((unsigned int)header->prog_size);
//     parse_data->header = header;
//     parse_data->instruction = my_calloc(sizeof(instruction_t *),
//         (unsigned int)header->prog_size);
//     if (analyse_instructions(parse_data, fptr, header->prog_size) == -1) {
//         fclose(fptr);
//         return -1;
//     }
//     fclose(fptr);
//     debug_info(parse_data);
//     return 0;
// }
