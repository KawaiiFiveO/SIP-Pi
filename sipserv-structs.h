//
// Created by chris on 16.02.2018.
//

// struct for app dtmf settings

#define MAX_DTMF_SETTINGS 16

struct dtmf_config {
    short id;
    short active;
    short processing_active;
    char *description;
    char *audio_response_file;
    char *tts_intro;
    char *tts_answer;
    char *cmd;
};

// struct for app configuration settings
struct app_config {
    short ipv6;
    char *sip_domain;
    unsigned int port;
    char *sip_user;
    char *sip_password;
    char *language;
    short record_calls;
    short silent_mode;
    char *tts;
    char *announcement_file;
    char *CallCmd;
    char *AfterMath;
    char *log_file;
    char *config_file;
    struct dtmf_config dtmf_cfg[MAX_DTMF_SETTINGS];
    short gpio_enable;
    short gpio_port[4];
    short interrupt_send_port;
    short dtmf_encoding;
    char* dtmf_forward_hostname;
    char* maild_audio_response_file;
};

struct app_config app_cfg;
