//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
  {"", "if $(wpctl get-volume @DEFAULT_SOURCE@ | grep -q '[MUTED]'); then echo ''; else echo ''; fi", 1, 0},
  {"", "$XDG_CONFIG_HOME/wm/someblocks/blocks/volume", 1, 0},
  {" ", "df -kh --output=avail /dev/mapper/root | tail -n1 | tr -d '[:blank:]'", 1, 0},
  // {" ", "top -bn 2 -d 0.01 | grep '^%Cpu' | tail -n1 | awk '{print ($2+$4+$6)\"%\"}'", 1, 0},
  {" ", "$XDG_CONFIG_HOME/wm/someblocks/blocks/cpu", 1, 0},
  {" ", "$XDG_CONFIG_HOME/wm/someblocks/blocks/mem", 1, 0},
  {"| ", "date '+%a %d-%m-%Y %H:%M '",					1,		0},
};



//sets delimeter between status commands. NULL character ('\0') means no delimeter.
// static char delim[] = " | ";
static char delim[] = "  ";
static unsigned int delimLen = 5;
