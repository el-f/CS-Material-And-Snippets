SendMode Input
 
_auto := true

XButton2::
{
if _auto
{
Loop
{
if GetKeyState("XButton2", "P")
{
send, {q down}
send, {e down}
sleep, 1
send, {e up}
send, {q up}
sleep 210
}
else
break
} ;; loop
} ;; if
} ;; XButton2
