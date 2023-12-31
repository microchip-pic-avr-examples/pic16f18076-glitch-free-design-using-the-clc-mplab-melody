<!-- Please do not change this logo with link -->
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Glitch-Free Design Using the Configurable Logic Cell (CLC) 

This example shows how to configure the Configurable Logic Cell (CLC) Peripheral on the PIC16F18076 to create a glitch-free clock signal.

## Related Documentation
- [PIC16F18076 Data Sheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC16F18056-76-28-40-Pin-Microcontroller-Data-Sheet-40002325B.pdf)
- [PIC16F18076 Family Product Page](https://www.microchip.com/wwwproducts/en/PIC16F18076)
- [Glitch-Free Design Using the Configurable Logic Cell (CLC) Application Note](https://www.microchip.com/en-us/application-notes/an3324)

## Software Used


- [MPLAB® X IDE](http://www.microchip.com/mplab/mplab-x-ide) 6.10.0 or newer
- [MPLAB Xpress IDE](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xpress) (alternative to MPLAB X IDE)
- [MPLAB XC8 Compiler](http://www.microchip.com/mplab/compilers) 2.41 or a newer compiler 
- [MPLAB Code Configurator (MCC)](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator) 5.3.7 or newer 
- [Microchip PIC16F1xxxx Series Device Support pack](https://packs.download.microchip.com/) 1.19.363 or newer Device Pack




## Hardware Used
- PIC16F18076 Curiosity Nano [(EV53Z50A)](https://www.microchip.com/en-us/development-tool/EV53Z50A)

## Introduction
Getting rid of glitches is a problem frequently encountered by digital designers  A 'glitch' is a signal which does not remain active for a full clock period.  If fed by a glitches signal, some of the clock line latches maybe updated while others won't modify.

This code example demonstrates how to implement a glitch-free design using the PIC16F18076.

## Setup
This code example uses the PIC16F18076 Curiosity Nano Board which includes the Numerically Controlled Oscillator (NCO) and Configurable Logic Cell (CLC) modules that are required for this application. Figure 1 shows a block diagram illustrating how to create the glitch-free signal by using CLC1, CLC2, and CLC3. CLC4 is used in this example to output the system clock (CLOCK).  Most of the configuration for this code example will be done using MCC Melody.

*Figure 1 - Creating Glitch-Free Clock Signal*


![Creating Glitch-Free Clock Signal](images/Creating_Glitch-Free_Clock_Signal.png)

### Setup - MPLABX and Melody Environment
- Step 1: Open up MPLABX v6.0.0 or newer
- Step 2: Create a new project using the following settings by selecting the "New Project" option under the "File" dropdown menu.
    - **Step 1 - "Choose Project"**: 
        - Select the 'Microchip Embedded' category 
        - Select the 'Standalone Project' project
        - Click 'Next'
    - **Step 2 - "Select Device"**: 
        - Select 'All Families' for family
        - Select 'PIC16F18076' for device
        - Select the Curiosity Nano board (connected to the computer) for tool
            - Note: 'No Tool' can also be selected for this field. It is important to note that a tool must eventually be selected in order for a device to be programmed.
        - Click 'Next'
    - **Step 3 - "Select Header"**: Not applicable for this code example.
    - **Step 4 - "Select Plugin Board"**: Not applicable for this code example.
    - **Step 5 - "Select Compiler"**:
        - Select the XC8 2.36 (or newer) for the compiler 
        - Click 'Next'
    - **Step 6 - "Select Project Name and Folder"**:
        - Enter the project name
        - Verify that the "Project Location" and "Project Folder" are correct
        - Ensure that the "Set as main project" checkbox has been selected
        - Click 'Finish'
- Step 3: Open up 'MCC' from the toolbar at the top (then go to Step 4)
    - If 'MCC' is not in the toolbar, click on 'MPLAB Code Configurator' and follow the 'Easy Installation' video. Then open up MCC.
- Step 4: Click 'Select MCC Melody' and then 'Finish' from the MCC Content Manager Wizard (red box in Figure 2 and Figure 3)

*Figure 2 - MCC Content Manager Wizard*

![MCC Content Manager Wizard](images/MCC_Content_Manager_Wizard.png)

*Figure 3 - MCC Content Manager Wizard (Finish)*

![MCC Content Manager Wizard (Finish)](images/MCC_Content_Manager_Wizard_Finish.png)
- Step 5: Add all four CLC modules and the NCO Module from the "Device Resources" list on the left side of the window (see red and green boxes in Figure 4) to the project by clicking the green "plus" marks. After doing this, open the "Project Resources" list and ensure that all of the modules have been successfully added to the project (blue box in Figure 5).

*Figure 4 - Device Resources for CLC and NCO*

![Device Resources for CLC and NCO](images/Device_Resources_for_CLC_and_NCO.png)

*Figure 5 - Project Resources for CLC and NCO*

![Project Resources for CLC and NCO](images/Project_Resources_for_CLC_and_NCO.png)

### Setup - CLC1 Configuration
Click on CLC1 in the Project Resources list to open the configuration menu. Within the menu, modify the following settings:
- **Logic Cell Mode bits:** Select 'OR-XOR' from the dropdown menu
- **Second Input:** Select 'Fosc' from the dropdown menu
- **Third Input:** Select 'CLC2_OUT' from the dropdown menu
- **Second OR Gate:** Select the second input to be 'Fosc'
- **Fourth OR Gate:** Select the third input to be 'CLC2_OUT'

These settings configure CLC1 as the logical XOR of the System Clock signal and the output of CLC2. Refer to Figure 6 for an illustration of all of the module configurations described above (red boxes in Figure 6).

*Figure 6 - CLC1 Configuration*

![Configuration of CLC1](images/Configuration_of_CLC1.png)

### Setup - CLC2 Configuration
Click on CLC2 in the Project Resources list to open the configuration menu. Within the menu, modify the following settings: 
- **Logic Cell Mode bits:** Select '1-input D flip-flop with S and R' from the dropdown menu
- **Enable CLC Interrupt:** Select 'Enable CLC Interrupt'
- **Enable Falling Interrupt:** Select 'Enable Falling Interrupt'
- **First Input:** Select 'CLCIN1' from the dropdown menu
- **Second Input:** Select 'Fosc' from the dropdown menu
- **Third Input:** Select 'CLC1_OUT' from the dropdown menu
- **Fourth Input:** Select 'LFINTOSC' from the dropdown menu
- **First OR Gate:** Select the third input to be 'CLC1_OUT', this ultimately becomes the clock line for the D flip-flop
- **Second OR Gate:** Select the first input to be 'CLCIN1', this ultimately becomes the data line (D) for the D flip-flop

These settings configure CLC2 as a D flip-flop using an asynchronous pulse as its input, which is clocked by the output of CLC1. Refer to Figure 7 for an illustration of all of the module configurations described above (red boxes in Figure 7).

*Figure 7 -  CLC2 Configuration*

![Configuration of CLC2](images/Configuration_of_CLC2.png)

### Setup - CLC3 Configuration
Click on CLC3 in the Project Resources list to open the configuration menu. Within the menu, modify the following settings:
- **Logic Cell Mode bits:** Select '4-input AND' from the dropdown menu
- **First Input:** Select 'CLCIN2' from the dropdown menu
- **Second Input:** Select 'Fosc' from the dropdown menu
- **Third Input:** Select 'CLC2_OUT' from the dropdown menu
- **Fourth Input:** Select 'TX1' from the dropdown menu
- **First OR Gate:** Select the NOT symbol on the right side of the gate
- **Second OR Gate:** Select the second input to be 'Fosc'
- **Third OR Gate:** Select the third input to be 'CLC2_OUT'
- **Fourth OR Gate:** Select the NOT symbol on the right side of the gate

These settings configure CLC3 to provide the logical AND of the asynchronous pulse and the output of CLC2. Refer to Figure 8 for an illustration of all of the module configurations described above (red boxes in Figure 8).

*Figure 8 -  CLC3 Configuration*

![Configuration of CLC3](images/Configuration_of_CLC3.png)

### Setup - CLC4 Configuration
Click on CLC4 in the Project Resources list to open the configuration menu. Within the menu, modify the following settings:
- **Logic Cell Mode bits:** Select '4-input AND' from the dropdown menu
- **First Input:** Select 'CLCIN3' from the dropdown menu
- **Second Input:** Select 'Fosc' from the dropdown menu
- **Third Input:** Select 'CLC2_OUT' from the dropdown menu
- **First OR Gate:** Select the NOT symbol on the right side of the gate
- **Second OR Gate:** Select the second input to be 'Fosc'
- **Third OR Gate:** Select the NOT symbol on the right side of the gate
- **Fourth OR Gate:** Select the NOT symbol on the right side of the gate

These settings configure CLC4 as a pass through of the system clock. Refer to Figure 9 for an illustration of all of the module configurations described above (red boxes in Figure 9).

*Figure 9 -  CLC4 Configuration*

![Configuration of CLC4](images/Configuration_of_CLC4.png)

### Setup - System Settings (Clock Control, Configuration bits, and Interrupt Manager)
Click on Clock Control in the Project Resources list to open the configuraton menu. Within the menu, modify the following settings:
- **Current Oscillator Source Select:** Select 'HFINTOSC_32MHz' from the dropdown menu
- **HF Internal Clock:** Select '16_MHz' from the dropdown menu
- **System Clock (Hz):** Verify that the Hz value updated to '16000000'

Refer to Figure 10 for an illustration of all of the configurations described above (red boxes in Figure 10).

*Figure 10 -  Clock Control Configuration*

![Clock Control Configuration](images/Clock_Control_Configuration.png)

Click on Configuration Bits in the Project Resources list to open the configuration menu.  Within the menu, modify only the following settings: NOTE: If any other settings are modified the example may not behave correctly. 
- **External Oscillator Selection bits:** Select 'Oscillator not enabled' from the dropdown menu
- **Reset Oscillator Selection bits:** Select 'HFINTOSC (32 MHz)' from the dropdown menu

These configuration bit settings are also shown within the red boxes in Figure 11.

*Figure 11 -  Configuration Bit Settings*

![Configuration Bit Settings](images/Configuration_Bit_Settings.png)

Click on Interrupt Manager in the Project Resouces list to open the configuration menu.  Verify that the menu looks like Figure 12. If it does not, check the 'Enable' box for CLC2 (so that it looks like Figure 12).

*Figure 12 -  Interrupt Manager Settings*

![Interrupt Manager Settings](images/Interrupt_Manager_Settings.png)

### Setup - NCO1
Click on NCO1 from the Project Resource list to open the configuration menu. Within the menu, modify the following settings in the order they are listed:
1. **CLC Clock (Hz):** Change the value to be 16MHz (16000000 Hz).
2. **Requested NCO Output Frequency:** Change the value to 11Hz (the value that corresponds to NCO1INCU = 0x0, NCO1INCH = 0x0, and NCO1INCL = 0x1).
3. **Clock Source:** Select 'CLC3_OUT' from the dropdown menu.

These NCO settings are also shown within the red boxes in Figure 13.

*Figure 13 -  Configuration of NCO1*

![Configuration of NCO1](images/Configuration_of_NCO1.png)

### Setup - Pin Configurations

Click on Pins from the Project Resources list to open the configuration menu and pins grid view.  Within the pins grid view, modify only the following pins:

- **CLC4 -- CLC4 -- Output** Click on PORTB, pin 1. This pin should have a green box with a closed lock.
- **CLC4 -- CLCIN0 -- Input** Click on PORTC, pin 7. This pin should have an orange box with an open lock.
- **CLC4 -- CLCIN3 -- Input** Click on PORTB, pin 7. This pin should have a green box with a closed lock.
- **CLC3 -- CLC3 -- Output** Click on PORTB, pin 3. This pin should have a green box with a closed lock.
- **CLC3 -- CLCIN2 -- Input** Click on PORTB, pin 4. This pin should have a green box with a closed lock.
- **CLC2 -- CLC2 -- Output** Click on PORTC, pin 3. This pin should have a green box with a closed lock.
- **CLC1 -- CLC1 -- Output** Click on PORTA, pin 2. This pin should have a green box with a closed lock.
- **CLC1 -- CLCIN0 -- Input** Click on PORTC, pin 7. This pin should have a green box with a closed lock.
- **NCO1 -- NCO1 -- Output** Click on PORTA, pin 5. This pin should have a green box with a closed lock.

Refer to Figure 14 for an illustration of all of the pin configurations described above (red boxes in Figure 14).

*Figure 14 -  Pins Grid View*

![Pins Grid View](images/Pins_Grid_View.png)


Within the configuration menu, uncheck the 'Analog' box for all pins. 

Figure 15 shows the configuration menu with no Analog checkboxes checked (red boxes in image).

*Figure 15 -  Pin Configuration Menu*

![Pin Configuration Menu](images/Pin_Configuration_Menu.png)


### Setup - Melody Notifications
When configuring the CLC and NCO modules, Melody generate a few different types of notifications. These notifications are consolidated into a list that can be found by clicking on the tab called 'Notifications[MCC]' (towards the bottom).  Figure 16 shows two types of notifications that may be listed; 'HINT' and 'WARNING'. 

*Figure 16 -  Melody Notification List*

![Melody Notification List](images/Melody_Notification_List.png)

The warnings for this project (referring to the CLC1, CLC2, CLC3, and CLC4 modules) are all 'HINT' notifications that are checking to make sure that the other CLC modules are configured since there are dependencies in the configurations. Since all four modules of the CLC are being used, then they should already be configured (refer to the CLC configuration sections).

The notifications regarding the 'Interrupt Manager' can be ignored in this example, since the Interrupt Manager was configured in Figure 12, which ensures the required interrupt code will be generated.

The notification generated, pertaining to the NCO1 module, is a 'WARNING' notification. This notification will be addressed in the section below titled 'Setup - Software' which will show how to set 'CLC3_OUT' as the clock source (see 'Application Code' section below).

### Setup - Software

Click the 'Generate' button within the Project Resources Menu to generate the code (Figure 17).

*Figure 17 -  Generate Code*

![Generate Code](images/Generate_Code.png)

A popup may appear once the 'Generate' button is clicked (see Figure 18).  Click on 'Yes' to continue.  The warning on the popup will be solved in the next section.


*Figure 18 -  Melody Code Warning*

![Melody Code Warning](images/Melody_Code_Warning.png)

#### Application Code

Next, the CLC3_OUT signal needs to be configured as a clock source (since it had the 'WARNING' notification).  This configuration will be done by setting the output bit for the CLC3 module.  To do this, navigate to the  `main.c` file in Figure 19.

*Figure 19 -  Navigate to `main.c`*

![Navigate to main.c](images/Navigate_to_maindotc.png)

Open up the `main.c` source file. Insert the following code inside the 'int main(void)' loop after the 'SYSTEM_Initialize();' line but above the 'while(1)' loop:

    CLCDATA = 0x4; //set CLC3_OUT output bit
    
    NCO1CONbits.EN = 0;  //disable NCO module
           
Insert the following code inside the  'while(1)' loop:

    //wait initialize
    NCO1ACCL = 0x00; 
    NCO1ACCH = 0x00; 
    NCO1ACCU = 0x00;  //clear accumulator

    NCO1CONbits.EN = 1; //enable NCO module
    PIR2bits.CLC2IF = 0; //clear CLC2IF interrupt flag
    
    //wait for pulse
    while(!PIR2bits.CLC2IF); //wait until interrupt flag is set

        //save accumulator value
        int8_t result2 = NCO1ACCU; 
        int8_t result1 = NCO1ACCH;
        int8_t result0 = NCO1ACCL;

        //process accumulator values to make a 20-bit value
        int24_t measurement = ((int24_t)result2 << 16); 
        measurement = measurement + ((int16_t)result1 << 8);
        measurement = measurement + result0;

    NCO1CONbits.EN = 0; //disable NCO module

Refer to the main.c file in the MPLABX project for this code example to see the exact placement of this code snippet.

Program the device by clicking on the 'Make and Program Device Main Project' button on the taskbar (Figure 20).

*Figure 20 -  Make and Program Device Main Project Button*

![Make and Program Device Main Project Button](images/Make_and_Program_Device_Main_Project_Button.png)

Wait for the Output tab to show 'Programming Complete' (Figure 21) then proceed to the **Operation** section below.

*Figure 21 -  Programming Complete*

![Programming Complete](images/Programming_Complete.png)

## Operation

This example requires an external asynchronous signal source in order for it to behave as expected.  This can be acheived by using a function generator, another microcontroller, or any other method of producing a high or low pulse.

Before starting the asynchronous signal, ensure that there is a common ground between the devices, and that the input for the CLC is attached to the RA1 pin. After all of this has been done, start running the asynchronous pulse.

The following image shows the resulting waveforms for this code example, illustrating how the logic should behave during a single asynchronous pulse.

*Figure 22 -  Glitch-Free Clock Output*

![Glitch-Free Clock Output](images/Glitch\-Free_Clock_Output.png)

<!-- NOTE: The Asynchronous signal used for this example was another cnano board.  It followed the same timing configuration as the above cnano but for the pin output it only had RA3 toggling on and off.  In between the high and low signal, there was 1us delay. Between the low and high signal, there was a 50us delay. Then the RA3 pin (of the asynchronous signal) was connected to the RA1 pin (of the CLC modules). -->

## Summary

This example has demonstrated how to create a glitch-free design using the CLC and NCO peripherals on the PIC16F18076 device.
