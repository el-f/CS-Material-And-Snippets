# E. Fine's Scripts For foobar2000 

### Audioscrobbler/foo_scrobble (Field remappings):
	
- Artist:
    ```
    [$if([%artist%],%artist%,$substr(%filename%,0,$strstr(%filename%, - )))]
    ```

- Title:
    ```
    [$if([%artist%],%title%,$substr(%filename%,$add($strstr(%filename%, - ),3),$len(%filename%)))]
    ```
    <br>

### Playlist View (Custom Columns):

- Artist:
    ```
    [$if([%artist%],%artist%,$substr(%filename%,0,$strstr(%filename%, - )))]
    ```

- Title:
    ```
    [$iflonger([$if([%artist%],%artist%,$substr(%filename%,0,$strstr(%filename%, - )))],1,[$if([%artist%],%title%,$substr(%filename%,$add($strstr(%filename%, - ),3),$len(%filename%)))],%title%)]
    ```
    <br>

### Playback state Display formatting:
	
- Window title:
    ```
    [%album artist% - ]['['%album%[ CD%discnumber%][ #%tracknumber%]']' ]%title%[ '//' %track artist%] - %playback_time%[ / %length%]
    ```

- Status bar:
    ```
    %codec%[ - %codec_profile%] | %bitrate% kbps | %samplerate% Hz | %filesize_natural% $if($or($greater($div($mul(100, %playback_time_seconds%), %length_seconds%), 50), $greater(%playback_time_seconds%, 240)), | scrobbled ✔, )
    ```

- Notification area icon tooltip:
    ```
    [%artist% - ]%title%
    ```
    <br>

### On-Screen Display:
		
- Title auto-pop:
    ```
    $rgb(255,255,255) [%artist% -] %title% [ '['$ifequal(%playback_time_seconds%, 0,,%_time_elapsed% / )%length%']']$if(%_ispaused%,'  <Paused>')
    $ifgreater(%playback_time_seconds%, 4,$crlf() $progress2(%_time_elapsed_seconds%, %_time_total_seconds%,30,■,□),)
    ```
    <br>

### Text Display (Acting as now-playing display area):
	
- Settings:
    ```
    $repeat(-,420)$crlf()
    $if(%isplaying%,$if(%ispaused%,||,▶),■)$crlf()
    [[$iflonger([$if([%artist%],%artist%,$substr(%filename%,0,$strstr(%filename%, - )))],1,[$if([%artist%],%title%,$substr(%filename%,$add($strstr(%filename%, - ),3),$len(%filename%)))],%title%)]$crlf()]
    [[$if([%artist%],%artist%,$substr(%filename%,0,$strstr(%filename%, - )))]$crlf()]
    [%playback_time% / ][%length%]$crlf()
    ['//'%directoryname%]$crlf()
    $repeat(-,420)
    ```
    <br>
    
### Autoplaylist:

- Long Files (over an hour):
	```
	%length% GREATER 59:59 SORT DESCENDING BY %length%
	```
- FLAC Files:
	```
	%codec% IS FLAC
	```
- Files With Hebrew:
	```
	%filename% HAS א OR %filename% HAS ב OR %filename% HAS ג OR %filename% HAS ד OR %filename% HAS ה OR %filename% HAS ו OR %filename% HAS ז OR %filename% HAS ח OR %filename% HAS ט OR %filename% HAS י OR %filename% HAS כ OR %filename% HAS ל OR %filename% HAS מ OR %filename% HAS נ OR %filename% HAS ס OR %filename% HAS ע OR %filename% HAS פ OR %filename% HAS צ OR %filename% HAS ק OR %filename% HAS ר OR %filename% HAS ש OR %filename% HAS ת OR %filename% HAS ף OR %filename% HAS ך OR %filename% HAS ץ OR %filename% HAS ן
	```
- Recent Files (last 52 weeks):
	```
	%last_played% DURING LAST 52 WEEKS SORT DESCENDING BY %last_played%
	```
	<br>
