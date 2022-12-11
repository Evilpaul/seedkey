using skwrapper;
using System;

namespace csharp_test
{
    internal class Program
    {
        static void Main(string[] args)
        {
            VKeyGenResultExOpt retVal;
            uint oActualKeyArraySize;
            uint iSecurityLevel = 1;
            string ipVariant = string.Empty;
            string ipOptions = "01234567890123456";
            byte[] iopKeyArray = new byte[16];
            byte[] ipSeedArray = new byte[16];

            seedkeywrapper skw = new seedkeywrapper();

            Console.WriteLine($"Calling {nameof(skw.returnOnly)}");
            retVal = skw.returnOnly();
            Console.WriteLine($"{Enum.GetName(typeof(VKeyGenResultExOpt), retVal)}");

            Console.WriteLine($"Calling {nameof(skw.seedOnly)}");
            skw.seedOnly(ipSeedArray);
            Console.WriteLine($"Calling {nameof(skw.securityLevelOnly)}");
            skw.securityLevelOnly(iSecurityLevel);
            Console.WriteLine($"Calling {nameof(skw.variantOnly)}");
            skw.variantOnly(ipVariant);
            Console.WriteLine($"Calling {nameof(skw.optionsOnly)}");
            skw.optionsOnly(ipOptions);

            Console.WriteLine($"Calling {nameof(skw.keyOnly)}");
            skw.keyOnly(out iopKeyArray);
            foreach (int element in iopKeyArray)
            {
                Console.Write($"{element } ");
            }
            Console.WriteLine();

            Console.WriteLine($"Calling {nameof(skw.actualKeySizeOnly)}");
            skw.actualKeySizeOnly(out oActualKeyArraySize);
            Console.WriteLine($"{oActualKeyArraySize}");

            Console.WriteLine($"Calling {nameof(skw.GenerateKeyExOpt)}");
            retVal = skw.GenerateKeyExOpt(ipSeedArray, iSecurityLevel, ipVariant, ipOptions, out iopKeyArray, out oActualKeyArraySize);
            Console.WriteLine($"{retVal}");
            foreach (int element in iopKeyArray)
            {
                Console.Write($"{element} ");
            }
            Console.WriteLine();
            Console.WriteLine($"{oActualKeyArraySize}");
        }
    }
}
