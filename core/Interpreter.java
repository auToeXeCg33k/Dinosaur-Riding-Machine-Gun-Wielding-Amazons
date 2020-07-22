package core;

import units.*;

public class Interpreter {
    private byte state;
    private final Tracker tracker;
    private final Data data;

    public Interpreter() {
        this.state = 0;
        this.tracker = new Tracker();
        this.data = new Data();
    }


    public Report interpret(String input) {
        if (input.equalsIgnoreCase("exit"))
            System.exit(0);


        switch (this.state) {
            case 0:
                try {
                    byte b = Byte.parseByte(input);
                    Report report = this.data.startGame(b);
                    if (report.getCode())
                        this.state++;
                    return new Report(report.getPrint() + (report.getCode() ? "\nPlayer 1 parancsa:\n" : ""), false);
                } catch (Exception e) {
                    return new Report ("Ez nem is szám more. Retry: ", false);
                }

            case 1:
                String[] words = input.split(" ");

                if (words[0].equals(""))
                    return new Report("Há, azé írhatná be valamit...\n", false);

                if (words[0].equalsIgnoreCase("exit"))
                    System.exit(0);

                if (data.getCommands().get(words[0].toLowerCase()) == null)
                    return new Report("Ilyen parancs nincs is bruh!\n", false);

                Report commandReport = this.data.getCommands().get(words[0].toLowerCase()).execute(words, this.data);
                if (commandReport.getCode())
                    return commandReport;

                String temp = this.tracker.track(this.data);
                if (temp != null) {
                    this.state++;
                    return new Report(commandReport.getPrint().concat(temp), false);
                }

                return new Report(commandReport.getPrint().concat("\nPlayer " + (this.data.getPlayerMarker() ? "2" : "1") + " parancsa:\n"), false);


            case 2:
                System.exit(0);


            default:
                return new Report("", false);
        }
    }
}
