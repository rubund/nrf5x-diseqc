#ifndef INCLUDE_DISEQC_CONSTANTS
#define INCLUDE_DISEQC_CONSTANTS


#define FRAMING_COMMAND_FROM_MASTER_NO_REPLY_REQUIRED_FIRST                     0xE0
#define FRAMING_COMMAND_FROM_MASTER_NO_REPLY_REQUIRED_REPEATED                  0xE1
#define FRAMING_COMMAND_FROM_MASTER_REPLY_REQUIRED_FIRST                        0xE2
#define FRAMING_COMMAND_FROM_MASTER_REPLY_REQUIRED_REPEATED                     0xE3
#define FRAMING_REPLY_FROM_SLAVE_OK                                             0xE4
#define FRAMING_REPLY_FROM_SLAVE_COMMAND_NOT_SUPPORTED                          0xE5
#define FRAMING_REPLY_FROM_SLAVE_PARITY_ERROR                                   0xE6
#define FRAMING_REPLY_FROM_SLAVE_COMMAND_NOT_RECOGNIZED                         0xE7

#define ADDRESS_ANY_DEVICE                                                      0x00
#define ADDRESS_ANY_LNB_SWITCHER_SMATV                                          0x10
#define ADDRESS_LNB                                                             0x11
#define ADDRESS_LNB_WITH_LOOP_THROUGH_SWITCHING                                 0x12
#define ADDRESS_ANY_POLARISER                                                   0x20
#define ADDRESS_ANY_POSITIONER                                                  0x30
#define ADDRESS_POLAR_POSITIONER                                                0x31
#define ADDRESS_ELEVATION_POSITIONER                                            0x32

#define COMMAND_DRIVE_MOTOR_EAST                                                0x68
#define COMMAND_DRIVE_MOTOR_WEST                                                0x69

#endif /* INCLUDE_DISEQC_CONSTANTS */
