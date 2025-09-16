#include "basic.h"
#include <string.h>

#define CMD_BUF_SIZE 64

char cmd_buf[CMD_BUF_SIZE];
int cmd_len = 0;

void setup_basic();
int loop_basic();

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  setup_basic();
  show_prompt();
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      Serial.println();
      cmd_buf[cmd_len] = '\0';
      process_command(cmd_buf);
      cmd_len = 0;
      show_prompt();
    } else if (c >= ' ' && cmd_len < CMD_BUF_SIZE - 1) {
      cmd_buf[cmd_len++] = toupper(c);
      Serial.print(c);
    } else if (c == '\b' && cmd_len > 0) {
      cmd_len--;
      Serial.print("\b \b");
    }
  }
}

void show_prompt() {
  Serial.println();
  Serial.print("> ");
}

void process_command(char *cmd) {
  char *command = strtok(cmd, " ");
  if (command == NULL) {
    return;
  }

  if (strcmp(command, "HELP") == 0) {
    command_help();
  } else if (strcmp(command, "CLEAR") == 0) {
    command_clear();
  } else if (strcmp(command, "BASIC") == 0) {
    command_basic();
  } else if (strcmp(command, "PINMODE") == 0) {
    command_pinmode();
  } else if (strcmp(command, "DOUT") == 0) {
    command_dout();
  } else if (strcmp(command, "DIN") == 0) {
    command_din();
  } else if (strcmp(command, "AOUT") == 0) {
    command_aout();
  } else if (strcmp(command, "AIN") == 0) {
    command_ain();
  } else {
    Serial.print("Unknown command: ");
    Serial.println(command);
  }
}

void command_help() {
  Serial.println("Available commands:");
  Serial.println("  HELP          - Show this help message");
  Serial.println("  CLEAR         - Clear the screen");
  Serial.println("  BASIC         - Enter the BASIC interpreter. Type EXIT to l
eave.");
  Serial.println("  PINMODE <p> <m> - Set pin <p> to mode <m> (0=IN, 1=OUT, 2=P
ULLUP)");
  Serial.println("  DOUT <p> <v>    - Digital write value <v> to pin <p>");
  Serial.println("  DIN <p>         - Digital read from pin <p>");
  Serial.println("  AOUT <p> <v>    - Analog write value <v> to pin <p>");
  Serial.println("  AIN <p>         - Analog read from pin <p>");
}

void command_clear() {
  Serial.write(27);       // ESC
  Serial.print("[2J");    // Clear screen
  Serial.write(27);       // ESC
  Serial.print("[H");     // Home cursor
}

void command_basic() {
  Serial.println("Entering BASIC interpreter. Type EXIT to leave.");
  while(1) {
      if (loop_basic() != 0) {
          break;
      }
  }
}

void command_pinmode() {
    char *pin_str = strtok(NULL, " ");
    char *mode_str = strtok(NULL, " ");
    if (pin_str == NULL || mode_str == NULL) {
        Serial.println("Usage: PINMODE <pin> <mode>");
        return;
    }
    int pin = atoi(pin_str);
    int mode = atoi(mode_str);
    if (mode == 0) {
        pinMode(pin, INPUT);
    } else if (mode == 1) {
        pinMode(pin, OUTPUT);
    } else if (mode == 2) {
        pinMode(pin, INPUT_PULLUP);
    } else {
        Serial.println("Invalid mode. Use 0 for INPUT, 1 for OUTPUT, 2 for INPU
T_PULLUP.");
    }
}

void command_dout() {
    char *pin_str = strtok(NULL, " ");
    char *val_str = strtok(NULL, " ");
    if (pin_str == NULL || val_str == NULL) {
        Serial.println("Usage: DOUT <pin> <value>");
        return;
    }
    int pin = atoi(pin_str);
    int val = atoi(val_str);
    digitalWrite(pin, val);
}

void command_din() {
    char *pin_str = strtok(NULL, " ");
    if (pin_str == NULL) {
        Serial.println("Usage: DIN <pin>");
        return;
    }
    int pin = atoi(pin_str);
    int val = digitalRead(pin);
    Serial.println(val);
}

void command_aout() {
    char *pin_str = strtok(NULL, " ");
    char *val_str = strtok(NULL, " ");
    if (pin_str == NULL || val_str == NULL) {
        Serial.println("Usage: AOUT <pin> <value>");
        return;
    }
    int pin = atoi(pin_str);
    int val = atoi(val_str);
    analogWrite(pin, val);
}

void command_ain() {
    char *pin_str = strtok(NULL, " ");
    if (pin_str == NULL) {
        Serial.println("Usage: AIN <pin>");
        return;
    }
    int pin = atoi(pin_str);
    int val = analogRead(pin);
    Serial.println(val);
}

// A case-insensitive string comparison function
int stricmp(const char* s1, const char* s2) {
  while (*s1 && (tolower(*s1) == tolower(*s2))) {
    s1++;
    s2++;
  }
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
