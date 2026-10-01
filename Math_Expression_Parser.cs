namespace Calculadora._1_Desarrollo_de_software_I;
class Program
{
    static void Main(string[] args)
    {
        Console.Clear();
        bool continuar = true;
        while (continuar)
        {
            bool exito = true;
            Console.Write("Ingrese el calculo (escriba 'salir' para terminar el programa): ");
            string calc = Console.ReadLine();
            if (calc.ToLower().Replace(" ", "") == "salir")
            {
                Console.WriteLine("Saliendo del programa.");
                continuar = false;
            }
            else if (string.IsNullOrWhiteSpace(calc))
            {
                Console.WriteLine("Entrada vacía. Por favor, ingrese un cálculo válido o 'salir' para terminar.");
            }
            else
            {
                List<string> piezas;
                if (calc.Contains(' '))
                {
                    piezas = new List<string>(calc.Split(' ', StringSplitOptions.RemoveEmptyEntries));
                }
                else
                {
                    string box = "";
                    foreach (char caracter in calc)
                    {
                        if (caracter != '+' && caracter != '-' && caracter != '*' && caracter != '/' && caracter != '%')
                        {
                            box += caracter;
                        }
                        else
                        {
                            box += " " + caracter + " ";
                        }
                    }
                    piezas = new List<string>(box.Split(' ', StringSplitOptions.RemoveEmptyEntries));
                }
                // Buscar operadores *, /, % y resolverlos primero
                for (int i = 1; i < piezas.Count; i++)
                {
                    if (piezas[i] == "*" || piezas[i] == "/" || piezas[i] == "%")
                    {
                        string operador = piezas[i];
                        decimal numero1 = Convert.ToDecimal(piezas[i - 1]);
                        decimal numero2 = Convert.ToDecimal(piezas[i + 1]);
                        decimal resultado = 0;
                        switch (operador)
                        {
                            case "*":
                                resultado = numero1 * numero2;
                                break;
                            case "/":
                                if (numero2 != 0)
                                {
                                    resultado = numero1 / numero2;
                                }
                                else
                                {
                                    Console.WriteLine("Error: División por cero no permitida.");
                                    exito = false;
                                    break;
                                }
                                break;
                            case "%":
                                if (numero2 != 0)
                                {
                                    resultado = numero1 % numero2;
                                }
                                else
                                {
                                    Console.WriteLine("Error: Módulo por cero no permitido.");
                                    exito = false;
                                    break;
                                }
                                break;
                        }
                        piezas[i - 1] = resultado.ToString();
                        piezas.RemoveAt(i); // Eliminar el operador
                        piezas.RemoveAt(i); // Eliminar el segundo número (ahora en la posición i)
                        i--; // Retroceder el índice para revisar el nuevo operador en la posición actual
                    }
                }
                if (exito)
                {
                    for (int i = 1; i < piezas.Count; i++)
                    {
                        if (piezas[i] == "+" || piezas[i] == "-")
                        {
                            string operador = piezas[i];
                            decimal numero1 = Convert.ToDecimal(piezas[i - 1]);
                            decimal numero2 = Convert.ToDecimal(piezas[i + 1]);
                            decimal resultado = 0;
                            switch (operador)
                            {
                                case "+":
                                    resultado = numero1 + numero2;
                                    break;
                                case "-":
                                    resultado = numero1 - numero2;
                                    break;
                            }
                            piezas[i - 1] = resultado.ToString();
                            piezas.RemoveAt(i); // Eliminar el operador
                            piezas.RemoveAt(i); // Eliminar el segundo número (ahora en la posición i)
                            i--; // Retroceder el índice para revisar el nuevo operador en la posición actual
                        }
                    }
                }
                if (exito)
                {
                    Console.WriteLine($"Resultado: {piezas[0]}");
                }
                Console.ReadKey();
                Console.Clear();
            }
        }
    }
}
