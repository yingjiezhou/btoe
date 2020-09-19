#!/bin/bash
date

if [ -f List/AuAu200_day.lis ]; then
  mv List/AuAu200_day.lis List/AuAu200_day_old.lis
fi
cp blank List/AuAu200_day.lis

if [ -f List/AuAu200_day_current.lis ]; then
   rm List/AuAu200_day_current.lis
fi
cp blank List/AuAu200_day_current.lis

ls -1 /gpfs04/star/temp/OSG/ >> List/AuAu200_day.lis 

for day in `cat List/AuAu200_day.lis`
do
  echo ${day}
  if [ -f List/day${day}.lis ]; then
    mv List/day${day}.lis List/day${day}_old.lis
  fi
  cp blank List/day${day}.lis
  if [ -f List/day${day}_current.lis ]; then
    rm List/day${day}_current.lis
  fi
  cp blank List/day${day}_current.lis
  ls -1 /gpfs04/star/temp/OSG/${day} >> List/day${day}_current.lis
  cat List/day${day}_current.lis List/day${day}_old.lis | sort | uniq >> List/day${day}.lis
done
