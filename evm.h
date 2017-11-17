/* 
 * File:   evm.h
 * Author: yango
 *
 * Created on 9 de julio de 2014, 20:06
 */

#ifndef EVM_H
#define	EVM_H



#include <stdint.h>



#define EP_PROGRAM_SIZE 100 // 100 ins
#define EP_INSTRUCTION_SIZE 12 //4 OP code + 8 bits
#define EP_MEMORY_SIZE  (EP_INSTRUCTION_SIZE * EP_PROGRAM_SIZE)

enum ENGINE_PROGRAM_STATUS
{
    EPS_STOP, EPS_ERROR, EPS_RUNNING, EPS_WAIT_SIGNAL, EPS_WAIT_MS
};


enum ENGINE_PROGRAM_INS_CODE
{
    EPC_NOP,
    EPC_SETPORT_B = 1,
    EPC_SETPORT_C,
    EPC_SETPORT_D,
    EPC_SETPORT_EL,
    EPC_SETPORT_EH,
    EPC_WAIT_MS,
    EPC_WAIT_SIGNAL,
    EPC_EMIT_SIGNAL,
    EPC_JMP_INC,
    EPC_JMP_DEC,
    EPC_END
};

#ifdef	__cplusplus
extern "C" {
#endif



void evm_init();

void evm_start_executing();

void evm_stop_executing();

void evm_run();





#ifdef	__cplusplus
}
#endif

#endif	/* EVM_H */

