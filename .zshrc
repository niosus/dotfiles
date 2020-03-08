# Init antigen.
[ -s "$HOME/.antigen.zsh" ] && source "$HOME/.antigen.zsh"

# Configure antigen.
antigen use oh-my-zsh

# plugins
antigen bundle git
antigen bundle dirhistory
antigen bundle command-not-found
antigen bundle zsh-users/zsh-completions
antigen bundle zsh-users/zsh-syntax-highlighting
antigen bundle mafredri/zsh-async
antigen bundle jackwish/bazel

# Set theme.
antigen theme subnixr/minimal

# Apply antigen settings.
antigen apply

# Use Python 3 by default.
alias python=python3
alias pip=pip3

# Source ROS
source /opt/ros/melodic/setup.zsh
source ~/Code/catkin_ws/devel/setup.zsh
