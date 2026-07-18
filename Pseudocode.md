# **<u>PSEUDOCODE</u>** 

BEGIN 

Display “MOTOR CURRENT SAFETY MONITORING SYSTEM” 

Input number Of Motors 

Safe Motor – 0 

Overloaded Motor – 0 

Open motor_current_report.text 

For each motor From 1 To number Of Motors 

Input motor Name 

Input rated Current 

Input measured Current 

IF rated Current <0 OR measured Current <0 THEN 

Display “Invalid Current Value” 

Write “Invalid Current Value” 

ELSE 

Current Difference – measured Current – rated Current IF measured Current <= rated Current 

# THEN 

status – “Safe Operation” 

safe Motor – safe Motor + 1 

ELSE 

status – “Overload Warning” 

overload Motors – overloaded Motors + 1 

END IF 

Display motor Name 

Display rated Current Display current Difference 

Display status 

Write all details to file 

END IF 

END FOR 

Display “FINAL REPORT” 

Display Total Motors Display Safe Motors 

Display Overloaded Motors 

Write final summary to file 

Close file 

Display “Report Saved Successfully” END 

