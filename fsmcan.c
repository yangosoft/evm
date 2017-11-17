#include "fsmcan.h"

#include "evm.h"

extern uint16_t device_id;


/* Flags ejecución programa motor */




extern uint8_t evm_memory [ EP_MEMORY_SIZE ];



uint8_t *pcurrentByte;


void fc_process_can_msg(CAN_MSG* msg)
{
    //Check if message if for us
    if ((device_id != msg->sid) && (0 != msg->sid))
    {
        return;
    }

    current_can_msg = *msg;
    fc_new_message = true;

    //Check command
    uint16_t command = (msg->data[0] >> 8) & (0x00FF);


    switch (command)
    {
        case FC_C_STOP:
            fc_process_state(FC_LISTEN);
            break;

        case FC_C_START_PROGRAMMING:
            fc_process_state(FC_START_PROGRAMMING);
            break;
        case FC_C_WRITE_INSTRUCTION:
            fc_process_state(FC_STORE_PROGRAM);
            break;

        case FC_C_END_PROGRAMMING:
            fc_process_state(FC_END_PROGRAMMING);
            break;

        case FC_C_EXECUTE:
            fc_process_state(FC_EXECUTE_PROGRAM);
            break;

        case FC_C_END_EXECUTE:
            fc_process_state(FC_LISTEN);
            break;

        case FC_C_SIGNAL:
            fc_process_state(FC_RECIEVE_SIGNAL);

            break;


        default:
            //ERROR
            break;


    }

    fc_new_message = false;





}

void fc_init()
{
    fc_current_state = FC_LISTEN;
    fc_new_message = false;
    fc_buffer_start = 0;
    fc_buffer_end = 0;

}

void fc_process_state(uint16_t status)
{

   

    switch (status)
    {
        case FC_LISTEN:
            //Do nothing
            fc_current_state = status;
            break;

        case FC_START_PROGRAMMING:
            
            evm_stop_executing();
            break;

        case FC_STORE_PROGRAM:
            fc_store_programm();
            fc_current_state = status;
            break;

        case FC_END_PROGRAMMING:
            fc_end_programming();
            fc_current_state = FC_LISTEN;
            break;

        case FC_EXECUTE_PROGRAM:
            fc_execute_program();
            fc_current_state = FC_LISTEN;
            break;

        case FC_RECIEVE_SIGNAL:
            fc_receive_signal();
            fc_current_state = FC_LISTEN;
            break;

    }


}

/**
 * Prepares to write program instruccion from CAN
 */
void fc_start_programming()
{
    pcurrentByte = &evm_memory[0];
}

/**
 * Extracts a program payload from CAN message
 * and stores it in memory program
 */
void fc_store_programm()
{

    if( (pcurrentByte + 6) >=  &evm_memory[EP_MEMORY_SIZE] )
    {
        //There is no space for  6 bytes
        return;

    }

  //dsPIC30F4012 es Little Endian. Comprobar que esto está bien
    //0
    *pcurrentByte = (uint8_t)(current_can_msg.data[0] & 0x00FF);
    pcurrentByte++;
    //1
    *pcurrentByte =  (uint8_t)((current_can_msg.data[1] >> 8) & 0x00FF) ;
    pcurrentByte++;
    *pcurrentByte = (uint8_t)(current_can_msg.data[1] & 0x00FF);
    pcurrentByte++;
    //2
    *pcurrentByte =  (uint8_t)((current_can_msg.data[2] >> 8) & 0x00FF) ;
    pcurrentByte++;
    *pcurrentByte = (uint8_t)(current_can_msg.data[2] & 0x00FF);
    pcurrentByte++;

    //3
    *pcurrentByte =  (uint8_t)((current_can_msg.data[3] >> 8) & 0x00FF) ;
    pcurrentByte++;

    if( pcurrentByte <  &evm_memory[EP_MEMORY_SIZE] )
    {

    
        *pcurrentByte = (uint8_t)(current_can_msg.data[3] & 0x00FF);
        pcurrentByte++;
    }



}

void fc_end_programming()
{


}

void fc_execute_program()
{
    evm_start_executing();
}

void fc_push_can_msg(CAN_MSG* msg)
{
    fc_can_buffer[ fc_buffer_end ] = *msg;

    fc_buffer_end++;
    if ( fc_buffer_end >= CAN_MSG_BUFFER_SIZE )
    {
        fc_buffer_end = 0;
    }
}

void fc_run()
{
    if ( fc_buffer_start != fc_buffer_end )
    {
        fc_process_can_msg( &fc_can_buffer[ fc_buffer_start ]  );

        fc_buffer_start++;

        if( fc_buffer_start >= CAN_MSG_BUFFER_SIZE )
        {
            fc_buffer_start = 0;
        }

    }

}

void fc_receive_signal()
{
    uint8_t signal_id = (uint8_t) (current_can_msg.data[0] & 0x00FF);

    //notificar al módulo evm
    //notificar al resto de módulos
}
