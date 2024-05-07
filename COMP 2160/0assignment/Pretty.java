import java.util.*;

/**
 * Pretty: A program that will "pretty print" plain text output by limiting
 * output lines to 80 characters.
 */
public class Pretty 
{
  /** The maximum number of characters allowed to be on one line. */
  public static final int LINE_SIZE = 80;

  public static void main(String[] parms) 
  {
    String inputLine;
    int position = 1;

    // read from standard input (we're not opening a file for reading, we're
    // just accepting whatever's typed in).
    try (Scanner fileIn = new Scanner(System.in)) 
    {

      while (fileIn.hasNextLine()) 
      {
        inputLine = fileIn.nextLine();

        // blank lines and lines that have text on them should be handled
        // differently from each other.
        if (inputLine.equals("")) 
        {
          // when we have already printed out *some* text but have encountered
          // a blank line, we should print out a newline to move to the next
          // character.
          if (position > 1) 
          {
            System.out.println();
          }

          // we should always print out a newline when we have read a blank line
          System.out.println();
          position = 1;
        }
        else 
        {
          if ((position + inputLine.length() - 1) > LINE_SIZE) 
          {
            // if printing this line would be wider than the line length, then
            // we should move to the next line to begin printing.
            System.out.println();
            position = 1;
          }

          // print out the current line, and move our position "pointer" just
          // past where the current line ends in output.
          System.out.print(inputLine);
          position += inputLine.length();

          if (position <= LINE_SIZE) { // add a blank after the current word
            System.out.print(" ");
            position++;
          }
        }
      }
    }
  }
}
