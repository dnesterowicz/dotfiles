# eval $(dircolors $XDG_CONFIG_HOME/colors)
(cat ~/.cache/wal/sequences &)

# Load aliases & functions
[ -f "${XDG_CONFIG_HOME:-$HOME/.config}/shell/aliasrc" ] && source "${XDG_CONFIG_HOME:-$HOME/.config}/shell/aliasrc"
[ -f "${XDG_CONFIG_HOME:-$HOME/.config}/shell/funcrc" ] && source "${XDG_CONFIG_HOME:-$HOME/.config}/shell/funcrc"

# Options
setopt autocd
setopt interactive_comments
setopt inc_append_history
setopt completealiases

# Vars
PS1="
%F{32}%~%f
$ "
HISTSIZE=100000
SAVEHIST=100000

# Tab autocompletion
autoload -U compinit
zstyle ':completion:*' menu select
zmodload zsh/complist
compinit


# Keybinds
autoload -z edit-command-line; 
zle -N edit-command-line
bindkey "^e" edit-command-line
zle -N fzf-open
bindkey "^o" fzf-open
bindkey -s ^t "tmux-sessionizer\n"

# Vi mode
source /usr/share/zsh/plugins/zsh-vi-mode/zsh-vi-mode.plugin.zsh

