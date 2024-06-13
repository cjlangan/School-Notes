import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Scanner;

public class Search
{
    public static void main(String[] args)
    {
        Collection<String> dictionary = new ArrayList<>();
        Collection<String> words = new ArrayList<>();

        try (Scanner sc = new Scanner(Path.of("/usr/share/dict/words")))
        {
            while (sc.hasNextLine())
            {
                dictionary.add(sc.nextLine());
            }
        }
        catch (final IOException e)
        {
            System.err.println("Failed to read dictionary.");
        }


        // add to words here:
        words.add("hello");

        for (final String s : words)
        {
            if (dictionary.contains(s))
            {
                System.out.printf("Found %s in dictionary.\n", s);
            }
        }
    }
}
