/* 
 * File:   fsmcan.h
 * Author: dzayas
 *
 * Created on 9 de julio de 2014, 7:30
 */

#ifndef FSMCAN_H
#define	FSMCAN_H

#include <stdint.h>
#include <stdbool.h>
#include "evm.h"

#ifdef	__cplusplus
extern "C" {
#endif

#define CAN_MSG_BUFFER_SIZE 10

    typedef struct {
        //SID of message
        uint16_t sid;

        //Data of message
        uint16_t data[4];

        //Length
        uint8_t data_length;

    } CAN_MSG;


    CAN_MSG fc_can_buffer[CAN_MSG_BUFFER_SIZE];
    CAN_MSG current_can_msg;

    enum FSM_CAN_STATUS {
        FC_LISTEN, FC_START_PROGRAMMING, FC_STORE_PROGRAM, FC_END_PROGRAMMING, FC_EXECUTE_PROGRAM, FC_EMIT_SIGNAL, FC_RECIEVE_SIGNAL
    };

    enum FSM_COMMANDS {
        FC_C_START_PROGRAMMING, FC_C_WRITE_INSTRUCTION, FC_C_STOP, FC_C_END_PROGRAMMING, FC_C_EXECUTE, FC_C_END_EXECUTE, FC_C_SIGNAL
    };

    /**
     * Init FSM
     */
    void fc_init();

    /**
     * Called from main loop
     */
    void fc_run();

    /**
     * Called to add a new CAN message to FSM CAN
     * @param msg
     */
    void fc_push_can_msg(CAN_MSG* msg);

    


    /*
     * Called each time there is a change in status
     */
    void fc_process_state(uint16_t status);



    /* Internal functions */

    //Index where current MSG unprocessed remains
    uint8_t fc_buffer_start;

    //Last index of last message inserted
    uint8_t fc_buffer_end;

    //Holds current state
    uint16_t fc_current_state;

    //internal flag
    bool fc_new_message;


    /*
     * Called in each fc_run  iteration
     * with a new message non processed
     */
    void fc_process_can_msg(CAN_MSG* msg);
    
    void fc_listen();
    void fc_start_programming();
    void fc_store_programm();
    void fc_end_programming();
    void fc_execute_program();
    void fc_receive_signal();
    
    


    


#ifdef	__cplusplus
}
#endif

#endif	/* FSMCAN_H */

