#! /usr/bin/perl

# This script is responsible for speaking out a date stamp.
# It should be installed in your voice directory once you got
# it working correctly.
#
# Input:  $1 - filename for which the date information should be spoken out
#         $2 - sample speed
#         $3 - modem type
#         $4 - compression type
#
# Output: rmd voice file on stdout
#
# This implementation uses GNU find and the rsynth synthesizer.

$tmp="/tmp";
$numbers_dir="/home/b_adele/tmp/sound/numero_data";
$numbers="";


#joue les fichiers
sub play_path
{
    system  "cat $_[0] > $tmp/file.raw";
    system "sox -t raw -r 8000 -swc1 $tmp/file.raw -t wav $tmp/wav.wav";
    system "play $tmp/wav.wav";  
}

# joue les nombres enumérés
sub play_enum_chiffre
{
    $file=get_enum_number($_[0]);
    play_path($file);
}


# retourne les chemins des fichiers à joué à la suite
sub get_enum_chiffre
{
    $result = $_[0];
    $result=~ s/([0-9])/$numbers_dir\/$1.wav.raw /g;
    return $result;
}

sub get_enum_dizaine
{
	$reste = $_[0] % 10;
	$dizaine = $_[0]-$reste;
	
	$result = "$numbers_dir/$dizaine.wav.raw ";
	if ($reste!=0) {
	    $result.= "$numbers_dir/$reste.wav.raw";
	}    
	return $result;
	
}

sub get_enum_centaine
{
      $nombre = substr($_[0],0,1);      
	
      if ($nombre>1) {
        $result = get_enum_chiffre($nombre);
      }		
      $result.= "$numbers_dir/100.wav.raw ";
      return $result;
      
}

sub get_number
{
    my $result;    
    if ($_[0]<20) { # inferieur à 20
        $result = $_[0];
        $result=~ s/([0-9]+)/$numbers_dir\/$1.wav.raw /g;
    } elsif ($_[0]<100) { # inferieur à 100
	$result = get_enum_dizaine($_[0]);
    } elsif ($_[0]<1000) { #inferieur à 1000
      #$result = get_enum_chiffre(substr($_[0],0,1));
      #$result.= "$numbers_dir/100.wav.raw ";
      $result = get_enum_centaine($_[0]);
      $result.= get_enum_dizaine(substr($_[0],1)); 
    }
    return $result;
} 

sub compte
{
    for ($i=0;$i<999;$i++) {
	play_path( get_number($i));
    }
}

#$nombre=say_number($ARGV[0]);
#system "play $nombre";

#play_enum_number("0467132454");
#print get_number($ARGV[0]);
play_path( get_number($ARGV[0]));
#compte();
