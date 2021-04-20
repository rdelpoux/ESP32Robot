## Motor with encoder

The mobile robot is made up of two [DC motors with encoders](https://store.digilentinc.com/dc-motor-gearbox-1-53-gear-ratio-custom-6v-motor-designed-for-digilent-robot-kits/) and two [2A-H-bridge](https://reference.digilentinc.com/reference/pmod/pmodhb5/reference-manual)

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/moteur-reducteur-avec-encodeur.png" alt="motor" width="300" />

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/pmodhb5-0.png" alt="Dual-brige " width="150" />

The H-bridge is a PmodHB5 whose block block diagram is :

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/Pmodblockdiagram.png" alt="Dual-brige " width="300" />

The PmodHB5 utilizes a full H-Bridge circuit to allow users to drive DC motors from the system board. Two sensor feedback pins are incorporated into the motor connection header.

### H-bridge

The H-bridge circuit principle is the following : 

<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/Hbridge.png" alt="Dual-brige " width="500" />



### Encoder

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html><head>
<title>Encoder Library, for Measuring Quadarature Encoded Position or Rotation Signals</title>
<base target="_top">
<link rel="shortcut icon" href="/favicon.ico">
<link rel="icon" href="/favicon.ico">
<link rel="stylesheet" href="/style.css" type="text/css">
<meta name="MSSmartTagsPreventParsing" content="TRUE">
<link rel="stylesheet" href="td_libs.css" type="text/css">
<script><!--
var img = new Array();
img[0] = new Image();
img[1] = new Image();
img[2] = new Image();
img[3] = new Image();
img[0].src = "https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos1.png";
img[1].src = "https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos2.png";
img[2].src = "https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos3.png";
img[3].src = "https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos4.png";
var position = 0;
function rotate(n) {
val = Number(document.getElementById('accum').value) + n;
if (isNaN(val)) val = 0;
document.getElementById('accum').value = val;
position += n;
if (position > 3) position = 0;
if (position < 0) position = 3;
document.getElementById('quad').src = img[position].src;
}
--></script>

Encoders can sense movement in either direction, by detecting holes or
marks as they move past 2 positions.  When the blue disc in the
diagram below spins clockwise, the changes are first detected by
pin 1, and then by pin 2.  When it spins counterclockwise, pin 2
is first to detect changes.  This scheme is called "quadrature encoding"
because the waveforms detected by the 2 pins are 90 degrees out of
phase.

<p>
<table align=center width=660>
<tr><td align=center height=244><img src="td_libs_Encoder_pos1.png" id="quad"></td></tr>
<tr><td align=center><form action="#">
<input type=submit value="<-- Counterclockwise" onClick="rotate(-1); return false">
<input type=text value="0" id="accum" size=6>
<input type=submit value="Clockwise -->" onClick="rotate(1); return false">
</form></td></tr>
</table>
<p>
The Encoder library monitors the 2 pins and updates a count of
the relative change in position.  The library updates its count at
each change, which is often called 4X counting, since 4 counts are
available for each physical mark or hole in the encoder hardware.
<!-- this hidden div provides links to all 4 images used by the
javascript above, so the archive site script will include them
in the downloadable ZIP file archive -->

<div id="td" style="position:absolute; left:-800; top:0; width:650; height:242; clip:rect(0,650,242,0); z-index:1; visibility:hidden;">
<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos1.png">
<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos2.png">
<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos3.png">
<img src="https://raw.githubusercontent.com/rdelpoux/ESP32Robot/main/img/td_libs_Encoder_pos4.png">
</div>

