#define END "\e[0m"
#define UNDSCORE(STRING) "\e[4m" STRING END
#define COLOR(X) "\e[38;5;" #X "m"
#define BACK_COLOR(X) "\e[48;5;" #X "m"
