#!/usr/bin/perl
# vim:expandtab:softtabstop=2:tabstop=2:shiftwidth=2:nowrap

package dtool;

use strict;
use warnings;

use File::Path;

my $fltk_dir_top= $ARGV[0];

if (not defined $fltk_dir_top)
{
  die('ARGV[0] missing. Must be FLTK top directory');
}

my $fltk_dir_h= "$fltk_dir_top/FL";
my $fltk_dir_s= "$fltk_dir_top/src";

my $tmp_dir_h= './tmpH'; 
my $tmp_dir_s= './tmpS'; 

mkdir('./regS');

rmtree($tmp_dir_h);
mkdir($tmp_dir_h);

rmtree($tmp_dir_s);
mkdir($tmp_dir_s);

my %ignore;

map_load_ignore('./mapign.txt');

my %map;

map_load('./maphdr.txt');
map_load('./mapsrc.txt');

copy_hdr();
copy_src();

rmtree($tmp_dir_h);
rmtree($tmp_dir_s);

sub map_load
{
	my $fname= shift or die "Empty file name\n";
  my $error= 0;
  my $no= 1;

  open(my $fp, '<', $fname) or die "Unable to open map: '$fname' $!\n";

  while (my $line = <$fp>)
  {
    chomp($line);
    my @v= split(',', $line);

    if (3 != scalar @v)
    {
      print ("invalid header line: $no\n");
      $error++;
    }

    $map{$v[0]}{'dest'}= $v[1];
    $map{$v[0]}{'clobber'}= $v[2];
    $no++;
  }

  close($fp);

  exit -1 if ($error);
}

sub map_load_ignore
{
	my $fname= shift or die "Empty file name\n";
  my $error= 0;
  my $no= 1;

  open(my $fp, '<', $fname) or die "Unable to open map: '$fname' $!\n";

  while (my $line = <$fp>)
  {
    chomp($line);
    $ignore{$line}= 1;
    $no++;
  }

  close($fp);

  exit -1 if ($error);
}

sub inc_replace
{
	my $line= shift;
  my $h;
  my $x= 0;

  if (not $line =~ m/\"(.*)\"/)
  {
		$line =~ m/<FL\/(.*)>/;
    $h= $1;
		if (not $h)
		{
			$line =~ m/<(.*)>/;
      $h= $1;
		}
  }
  else
  {
    $h= $1;
  }

  if ($h && defined $map{$h})
  {
		$line=~ s/$h/$map{$h}{'dest'}/;
    $line=~ s/FL/fl/;
  }

	if ($line =~ /<fl_math\.h>/)
	{
		$line=~ s/<fl_math\.h>/<fl\/fl_math.h>/;
	}
	elsif ($line =~ /<config\.h>/)
	{
		$line=~ s/</"/;
		$line=~ s/>/"/;
	}
	elsif ($line =~ /Fl_Help_Dialog\.H/)
	{
		$line= "#include <fl/dlghelp.h>\n";
	}
	elsif ($line =~ /Fl_File_Chooser\.H/)
	{
		$line= "#include <fl/filech.h>\n";
	}
	elsif ($line =~ /mk_wcwidth\.c/)
	{
		$line=~ s/mk_wcwidth/wcwidth/;
	}

  return $line;
}

sub diff_file
{
	my $fns= shift;
	my $fnd= shift;
	my $fnr= shift;
	my $clobber= shift;

	if (-e $fnd && !$clobber)
	{
		my $d= "$fns.diff";
		my $cmd= "diff --label regS -B -b -w -u $fns $fnd > $d";
		system($cmd);

		if (-e $fnr)
		{
			my $cmd= "diff $d $fnr";
			my $c= `$cmd`;
			if ($c)
			{
				print "$c $d : regress\n";
			}
		}
		else
		{
			my $cmd= "cp $d $fnr";
			system($cmd);
		}
	}
	else
	{
		my $cmd= "cp $fns $fnd";
		system($cmd);
	}
}

sub copy_file
{
	my $fns= shift or die "Unkown source file";
	my $fnd= shift or die "Unkown destination file";

	open(my $fps, '<', $fns) or die "Unable to open header '$fns' $!";
	open(my $fpd, '>', $fnd) or die "Unable to create header '$fnd' $!";

	while (my $line = <$fps>)
	{

		if ($line =~ /^#/ && $line =~ /include/)
		{
			if ($line =~ /abi-version/)
			{
					chomp($line);
					$line= "/* $line ALLEGRO: */\n";
			}
			else
			{
				$line= inc_replace($line);
			}
		}

		print $fpd $line;
	}

	close($fpd);
	close($fps);
}

sub copy_hdr
{
	opendir(my $fd, $fltk_dir_h) or die "Open error $fltk_dir_h: $!";

	while( my $fn = readdir($fd))
	{
		if($fn !~ m/^\.+/i)
		{
			if (not defined($map{$fn}))
			{
				if (not defined($ignore{$fn}))
				{
					print $fn."\n";
				}
			}
			else
			{
				my $fns= "$fltk_dir_h/$fn";
				my $fnd= "$tmp_dir_h/$map{$fn}{'dest'}";
				copy_file($fns, $fnd);
				my $fnf= "../fl/$map{$fn}{'dest'}";
				my $fnr= "regS/$map{$fn}{'dest'}.diff";
				diff_file($fnd, $fnf, $fnr, $map{$fn}{'clobber'});
			}
		}
	}

	closedir($fd);
}

sub copy_src
{
	opendir(my $fd, $fltk_dir_s) or die "Open error $fltk_dir_s: $!";

	while( my $fn = readdir($fd))
	{
		if($fn !~ m/^\.+/i)
		{
			if (not defined($map{$fn}))
			{
				if (not defined($ignore{$fn}))
				{
					print $fn."\n";
				}
			}
			else
			{
				my $fns= "$fltk_dir_s/$fn";
				my $fnd= "$tmp_dir_s/$map{$fn}{'dest'}";
				copy_file($fns, $fnd);
				my $fnf= "../src/$map{$fn}{'dest'}";
				my $fnr= "regS/$map{$fn}{'dest'}.diff";
				diff_file($fnd, $fnf, $fnr, $map{$fn}{'clobber'});
			}
		}
	}

	closedir($fd);
}

=cut

sub diff_src
{
  foreach my $src (keys %map_src)
  {
    my $fns= "$tmp_dir_s/$map_src{$src}{'header'}";
		my $fnd= "../src/$map_src{$src}{'header'}";

		if (-e $fnd && !$map_src{$src}{'clobber'})
		{
      my $d= "$fns.diff";
      my $cmd= "diff --label regS -B -b -w -u $fns $fnd > $d";
      system($cmd);

			my $r= "regS/$map_src{$src}{'header'}.diff";

			if (-e $r)
			{
				my $cmd= "diff $d $r";
				my $c= `$cmd`;
				if ($c)
				{
					print "$c $d : regress\n";
				}
			}
			else
			{
				my $cmd= "cp $d $r";
				system($cmd);
			}
		}
		else
		{
			my $cmd= "cp $fns $fnd";
			system($cmd);
		}
	}
}

sub map_auto
{
	foreach my $src (keys %map)
	{
		my $k= $src;
		$k=~ s/(\.cxx)/\.H/;
		if (defined($map{$k}))
		{
				my $t= $map{$k}{'dest'};
				$t=~ s/(\.cxx)/\.h/;
				$t=~ s/(\.c)/\.h/;
				$map{$k}{'dest'}= $t;
				$map{$k}{'clobber'}= 0;
		}
	}
}
