#!/bin/bash 

#Minor assignment 2
#Date: 03/02/23
#Description the program supposed to have a method to trap/scan for control C press, notated by Trap0handler and Trap Handler function it consists of the main program and two functions. Login_count Function counts the number of users, provides the user list and also inital users logged. It will sleep for 10 and then  resume the program again.

#Trap-handler
#-----------------------------
trap 'controlc' SIGINT #DETECTS WHEN CNTRL C IS PRESSED
#-----------------------------

#Trap-handler function
#-----------------------------
function controlc(){
  echo " SIGINT detected, please press Ctrl-C again to terminate the program."
#clear
  trap - SIGINT
#exit
  exit 0
}
#-----------------------------
#Variable definitions
#-----------------------------
logged_in_users=""
logged_out_users=""
previous_users_cnt=0
current_users_cnt=0          
#-----------------------------

#login_count function
function login_count(){

  #counts the number of lines of users
  current_users_cnt=$(who | wc -l)
  #cut to extract data, delimiter first field, usernames/IDS sorted alphabetically,
  current_users_list=$(who | cut -d " " -f1 | sort)

  #if previous user count does not equal current user count, check if any users have logged on since last check
  if [ "$previous_users_cnt" -ne "$current_users_cnt" ]; then
    #prints the current number of users
    echo "$(date) number of users connected: $current_users_cnt"
#iterates through the current userlist
    for user_iteration in $current_users_list; do
#checks if logged in users does not equal user_interation wild card added so we do not have to worry about position of where user iteration is added.
      if [[ "$logged_in_users" != *"$user_iteration"* ]]; then
#print date user_iteration logged into hostname
        echo "$(date) $user_iteration logged into $(hostname)"
#addition
        logged_in_users+="$user_iteration "
      fi
    done
#checks if logged in users does not equal user_interation wild card added so we do not have to worry about position of where user iteration is added.  
    for user_iteration in $logged_in_users; do
      if [[ "$current_users_list" != *"$user_iteration"* ]]; then
#prints date user_iteration logged out of hostname (cse machines)
        echo "$(date) $user_iteration logged out of $(hostname)"
#addition
        logged_out_users+="$user_iteration "
#can be treated as removing from list,/substitution
        logged_in_users=${logged_in_users/$user_iteration/}
      fi
    done
#changes value of previous_users_cnt
    previous_users_cnt=$current_users_cnt
  fi
}
#MAIN#
#-----------------------------
#while loop with sleep pause
echo "$(date) initial users logged"
while true; do
#call to function login_count
  login_count
  sleep 10
done

