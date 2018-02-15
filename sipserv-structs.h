//
// Created by chris on 16.02.2018.
//

// struct for app dtmf settings
struct dtmf_config {
    int id;
    int active;
    int processing_active;
    char *description;
    char *audio_response_file;
    char *tts_intro;
    char *tts_answer;
    char *cmd;
};

// struct for app configuration settings
struct app_config {
    int ipv6;
    char *sip_domain;
    int port;
    char *sip_user;
    char *sip_password;
    char *language;
    int record_calls;
    int silent_mode;
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
};

struct app_config app_cfg;
