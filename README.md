# vsss-comm-v1_0

This repository presents four directories, with varying applications in regards of the wireless communication used in the VSSS project for the UFPBots group, located at the Federal University of Paraiba, Joao Pessoa, Brazil.

%%%%%%%%%%%%%%%%%%%%%%%%%

CONTENT:
   ufpbots_spintest: Algorithm used to test the H-Bridge. Motors will turn clock-wise (can be altered in code if needed) at Half-Speed (50% of PWM duty cycle).
   
    ufpbots_spintest.ino      - Main File
  ufpbots_commtest_tx:  Algorithm used to test coherence in communication. Hexadecimal values for PWM can be sent through Serial and Robots can be turned on or off. Once turned on, the transmitter sends the preset value infinitely.
  

    output.h                  - Header with configurations for the output value
    ufpbots_commtest_tx.ino   - Main File
    
  ufpbots_transmissor3: Algorithm used to transmit data. Despite having a desired syntax, this code will send any 10-byte sized input placed on the serial buffer.
    
    Sintaxe.txt               - A quick textfile guide to the Syntax used by the platform to send data
    config.h	                - Header with configurations for the TX
    ufpbots_transmissor3.ino  - Main File
    
  ufpbots_receptor: Algorithm used to recieve data. Here, data recieved will be decoded according to the expected syntax, turning it in to PWM signals for the H-Bridge.
    
    bridgemap.h	              - Header with decoding formulas for the Logical Output Values
    config.h                  - Header with configurations for the RX
    print.h                   - Optional Header with functions to send over serial the recieved values (for debug purposes only)
    ufpbots_receptor.ino      - Main File
    
%%%%%%%%%%%%%%%%%%%%%%%%%

