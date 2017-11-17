/* 
 * File:   evm.c
 * Author: yango
 *
 * Created on 9 de julio de 2014, 20:06
 */

#include "evm.h"

uint8_t *evm_instruction_pointer;
uint8_t evm_memory [ EP_MEMORY_SIZE ];
uint16_t evm_program_status;


void evm_init()
{
    //Clear memory
    for(uint16_t i = 0; i < EP_MEMORY_SIZE ; i++ )
    {
        evm_memory[i] = EPC_NOP;
    }

    //Set instrucion pointer
    evm_instruction_pointer = &evm_memory[0];

    //Set status
    evm_program_status = EPS_STOP;

}

void evm_start_executing()
{
    evm_instruction_pointer = &evm_memory[0];
    evm_program_status = EPS_RUNNING;
}

void evm_run()
{
    //Si esta running
        //Coger 1 instrucción
        //Ejecutar
        //retorno
    //Si esta wait signal
    //si esta wait ms
}