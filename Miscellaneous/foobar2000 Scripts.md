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
    %codec%[ - %codec_profile%] | %bitrate% kbps | %samplerate% Hz | %filesize_natural%
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
