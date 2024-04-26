import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MarkdownFileProcessor {

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Usage: java MarkdownFileProcessor <input_file>");
            return;
        }

        String inputFile = args[0];
        String outputFile = "output.md"; // Change this to your desired output file path

        try {
            processMarkdownFile(inputFile, outputFile);
            System.out.println("Markdown file processed successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred while processing the Markdown file: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public static void processMarkdownFile(String inputFile, String outputFile) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(inputFile));
        BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile));

        String line;
        while ((line = reader.readLine()) != null) {
            // Replace occurrences of ![[file name.png]] with ![](/Images/file%20name.png)
            line = replaceImageLinks(line);

            writer.write(line);
            writer.newLine();
        }

        reader.close();
        writer.close();
    }

    private static String replaceImageLinks(String line) {
        Pattern pattern = Pattern.compile("!\\[\\[([^\\]]+)\\]\\]");
        Matcher matcher = pattern.matcher(line);
        StringBuffer stringBuffer = new StringBuffer();
        while (matcher.find()) {
            String fileName = matcher.group(1);
            String replacedFileName = fileName.replace(" ", "%20");
            matcher.appendReplacement(stringBuffer, "![](/Images/" + replacedFileName + ")");
        }
        matcher.appendTail(stringBuffer);
        return stringBuffer.toString();
    }
}

