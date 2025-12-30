autoload -U colors && colors	# Load colors
eval $(dircolors $XDG_CONFIG_HOME/colors)

# Options
setopt interactive_comments
setopt inc_append_history
setopt autocd
unsetopt BEEP
unsetopt LIST_BEEP

# Vars
PS1="
%F{32}%~%f
$ "
HISTSIZE=10000000
SAVEHIST=10000000

# Keybinds
autoload -z edit-command-line; zle -N edit-command-line; 
bindkey "^e" edit-command-line
bindkey -s ^f "tmux-sessionizer\n"

# Vi mode
source /usr/share/zsh/plugins/zsh-vi-mode/zsh-vi-mode.plugin.zsh

# Tab autocompletion
autoload -U compinit
zstyle ':completion:*' menu select
zmodload zsh/complist
compinit
_comp_options+=(globdots)	# Include hidden files.

# Load aliases
[ -f "${XDG_CONFIG_HOME:-$HOME/.config}/shell/aliasrc" ] && source "${XDG_CONFIG_HOME:-$HOME/.config}/shell/aliasrc"
