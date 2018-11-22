using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Lab_01
{
    class Algoritms
    {
        private string firstString;
        private string secondString;
        int[,] matrixLevenshtein;
        int[,] matrixDamerauLevenshtein;
        int countRec;


        Algoritms(string str1, string str2)
        {
            countRec = 0;
            firstString = str1;
            secondString = str2;
            matrixLevenshtein = new int[firstString.Length + 1, secondString.Length + 1];
            matrixDamerauLevenshtein = new int[firstString.Length + 1, secondString.Length + 1];
        }


        public int Levenshtein()
        {
            if (firstString == null) throw new ArgumentNullException("string1");
            if (secondString == null) throw new ArgumentNullException("string2");
            int diff;

            for (int i = 0; i <= firstString.Length; i++) { matrixLevenshtein[i, 0] = i; }
            for (int j = 0; j <= secondString.Length; j++) { matrixLevenshtein[0, j] = j; }

            for (int i = 1; i <= firstString.Length; i++)
            {
                for (int j = 1; j <= secondString.Length; j++)
                {
                    //Console.WriteLine("[First string: {0} First string: {1}]", firstString[i - 1], secondString[j - 1]);
                    diff = (firstString[i - 1] == secondString[j - 1]) ? 0 : 1;

                    matrixLevenshtein[i, j] = Math.Min(Math.Min(matrixLevenshtein[i - 1, j] + 1,
                                             matrixLevenshtein[i, j - 1] + 1),
                                             matrixLevenshtein[i - 1, j - 1] + diff);
                }
            }

            return matrixLevenshtein[firstString.Length, secondString.Length];
        }


               public int DamerauLevenshtein()
               {
                   if (firstString == null) throw new ArgumentNullException("string1");
                   if (secondString == null) throw new ArgumentNullException("string2");
                   int diff;

                   for (int i = 0; i <= firstString.Length; i++)
                       matrixDamerauLevenshtein[i, 0] = i;
                   for (int j = 0; j <= secondString.Length; j++)
                       matrixDamerauLevenshtein[0, j] = j;

                   for (int i = 1; i <= firstString.Length; i++)
                   {
                       for (int j = 1; j <= secondString.Length; j++)
                       {
                           diff = secondString[j - 1] == firstString[i - 1] ? 0 : 1;
                           var vals = new int[]
                           {
                               matrixDamerauLevenshtein[i - 1, j] + 1,
                               matrixDamerauLevenshtein[i, j - 1] + 1,
                               matrixDamerauLevenshtein[i - 1, j - 1] + diff
                           };
                           matrixDamerauLevenshtein[i, j] = vals.Min();
                           if (i > 1 && j > 1 && firstString[i - 1] == secondString[j - 2] && firstString[i - 2] == secondString[j - 1])
                               matrixDamerauLevenshtein[i, j] = Math.Min(matrixDamerauLevenshtein[i, j], matrixDamerauLevenshtein[i - 2, j - 2] + 1);
                       }
                   }


                   return matrixDamerauLevenshtein[firstString.Length, secondString.Length];
               }
       


        public int RecLevenshtein(string firstString, int firstStringLen, string secondString, int secondStringLen)
        {
            int diff;

            countRec++;

            if (firstStringLen == 0)
                return secondStringLen;
            if (secondStringLen == 0)
                return firstStringLen;

            if (firstString[firstStringLen - 1] == secondString[secondStringLen - 1])
                diff = 0;
            else
                diff = 1;

            //Console.WriteLine("[Rec First string: {0} First string: {1}]", firstString[firstStringLen - 1], secondString[secondStringLen - 1]);

            return Math.Min(Math.Min(RecLevenshtein(firstString, firstStringLen - 1, secondString, secondStringLen) + 1,
                            RecLevenshtein(firstString, firstStringLen, secondString, secondStringLen - 1) + 1),
                            RecLevenshtein(firstString, firstStringLen - 1, secondString, secondStringLen - 1) + diff);
        }


        public void WriteStr()
        {
            Console.WriteLine("\nFirst string: {0}\nSecond string: {1}\n", firstString, secondString);
        }


        public void WriteMatrix()
        {
            if(matrixLevenshtein != null)
            {
                Console.WriteLine("\nMatrix of Levenshtein:\n");
                for (int i = 0; i < matrixLevenshtein.GetLength(0); i++)
                {
                    for (int j = 0; j < matrixLevenshtein.GetLength(1); j++)
                        Console.Write("{0} ", matrixLevenshtein[i, j]);
                    Console.WriteLine();
                }
                Console.WriteLine("\nCountRec: {0}", countRec);
            }

            if (matrixDamerauLevenshtein != null)
            {
                Console.WriteLine("\nMatrix of Damerau–Levenshtein:\n");
                for (int i = 0; i < matrixDamerauLevenshtein.GetLength(0); i++)
                {
                    for (int j = 0; j < matrixDamerauLevenshtein.GetLength(1); j++)
                        Console.Write("{0} ", matrixDamerauLevenshtein[i, j]);
                    Console.WriteLine();
                }
            }
        }


        public void Test()
        {
            //Levenshtein
            Stopwatch sWatch = new Stopwatch();
            sWatch.Start();
            for (var i = 0; i != 1000; i++)
            {
                Levenshtein();
            }
            sWatch.Stop();

            Console.WriteLine("\nTime of Levenshtein: {0}", sWatch.ElapsedMilliseconds.ToString());

            //Damerau–Levenshtein
            Stopwatch sWatch2 = new Stopwatch();
            sWatch2.Start();
            for (var i = 0; i != 1000; i++)
            {
                DamerauLevenshtein();
            }
            sWatch2.Stop();

            Console.WriteLine("Time of Damerau–Levenshtein: {0}", sWatch2.ElapsedMilliseconds.ToString());

            //RecLevenshtein
            Stopwatch sWatch3 = new Stopwatch();
            sWatch3.Start();
            for (var i = 0; i != 1000; i++)
            {
                RecLevenshtein(firstString, firstString.Length, secondString, secondString.Length);
            }
            sWatch3.Stop();

            Console.WriteLine("Time of RecLevenshtein: {0}\n", sWatch3.ElapsedMilliseconds.ToString());
        }



    class Program
        {
            static void Main(string[] args)
            {
                Console.WriteLine("Input first word:");
                string firstString = Console.ReadLine();
                Console.WriteLine("Input second word:");
                string secondString = Console.ReadLine();

                Algoritms example = new Algoritms(firstString, secondString);

                Console.WriteLine("\nResult of Levenshtein: {0}", example.Levenshtein());
                Console.WriteLine("Result of Damerau–Levenshtein: {0}", example.DamerauLevenshtein());
                Console.WriteLine("Result of RecLevenshtein: {0}", example.RecLevenshtein(firstString, firstString.Length, secondString, secondString.Length));

                example.WriteMatrix();
                //example.Test();

                Console.ReadLine();
            }
        }
    }
}
