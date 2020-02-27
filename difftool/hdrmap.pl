#!/usr/bin/perl
# vim:expandtab:softtabstop=2:tabstop=2:shiftwidth=2:nowrap

my %hdr;
my $fname= 'hdrmap.txt';
my $fldir= $ARGV[0];
my $tmpdir='./fltmpH'; 

if (not defined $fldir)
{
  die('ARGV[1] missing. Must be FLTK directory');
}

map_load();
hdr_copy();
hdr_diff();

# do a diff on the mapped files to that in '../fl' directory
# ignore begining comment block (license)
sub hdr_diff()
{
  my $regr= 0;

  foreach $src (keys %hdr)
  {
    $regr= 0;
    $fns1= "$tmpdir/$hdr{$src}{'header'}";
    $fns2= "../fl/$hdr{$src}{'header'}";

    open(my $fps1, '<', $fns1) or die "Unable to open header '$fns1' $!";
    open(my $fps2, '<', $fns2) or die "Unable to open header '$fns2' $!";

    inc_skip($fps1);
    inc_skip($fps2);

    while(my $l1 = <$fps2>)
    {
      my $l2 = <$fps1>;
      $l1=~ s/\r//g;
      $l2=~ s/\r//g;
      $l1=~ s/^\s+//;
      $l2=~ s/^\s+//;
      if ($l1 ne $l2)
      {
        if (not $l1 =~ /^\/\//)
        {
          $regr= 1;
          last;    
        }
      }
    }

    if ($regr)
    {
      my $d= "$fns1.diff";
      my $cmd= "diff -B -b -w -u $fns1 $fns2 > $d";
      system($cmd);
    }

    close($fps2);
    close($fps1);
  }

}

# skip comment headers up to #define
sub inc_skip
{
  my $fp= shift(@_);

  while (my $line = <$fp>)
  {
    my $x= $line;
    $x=~ s/^\s+//;
    if (not $x =~ /^\/\//)
    {
      if ($x)
      {
        if ($x =~ /^#define/)
        {
          last;
        }
      }
    }
  }

}

# replace include macro with mapped header
sub inc_replace
{
  my $line= shift(@_);
  my $h;

  if (not $line =~ m/\"(.*)\"/)
  {
    $line =~ m/<(.*)>/;
    my $x= $1;
    if ($x)
    {
      $x =~ m/^FL\/(.*)/;
      $h= $1;
    }
  }
  else
  {
    $h= $1;
  }

  if ($h && defined $hdr{$h})
  {
    $line=~ s/$h/$hdr{$h}{'header'}/;
    $line=~ s/FL/fl/;
  }

  return $line;
}

# copy fltk headers into tmp directory 
# renames the header file to mapped file name
# changes include macros to mapped header
sub hdr_copy
{
  rmdir $tmpdir;
  mkdir $tmpdir;

  foreach my $src (keys %hdr)
  {
    my $fns= "$fldir/FL/$src";
    my $fnd= "$tmpdir/$hdr{$src}{'header'}";

    open(my $fps, '<', $fns) or die "Unable to open header '$fns' $!";
    open(my $fpd, '>', $fnd) or die "Unable to create header '$fnd' $!";

    while (my $line = <$fps>)
    {

      if ($line =~ /^#/ && $line =~ /include/)
      {
          $line= inc_replace($line);
      }

      print $fpd $line;

    }

    close($fpd);
    close($fps);
  }
}

# load map file info hash hdr
sub map_load
{
  my $error= 0;
  my $no= 1;

  open(my $fp, '<', $fname) or die "Unable to open map: '$fname' $!";

  while (my $line = <$fp>)
  {
    chomp($line);
    my @v= split(',', $line);

    if (3 != scalar @v)
    {
      print ("invalid header line: $no\n");
      $error++;
    }

    $hdr{$v[0]}{'header'}= $v[1];
    $hdr{$v[0]}{'clobber'}= $v[2];
    $no++;
  }

  close($fp);

  exit -1 if ($error);
}
