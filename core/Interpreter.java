package core;

import commands.Command;
import units.Report;

public class Interpreter {
  private byte state = 0;
  
  private final Tracker tracker = new Tracker();
  
  private final Data data = new Data();
  
  public Report interpret(String input) {
    String[] words;
    Report commandReport;
    String temp;
    if (input.equalsIgnoreCase("exit"))
      System.exit(0); 
    switch (this.state) {
      case 0:
        try {
          byte b = Byte.parseByte(input);
          Report report = this.data.startGame(b);
          if (report.getCode())
            this.state = (byte)(this.state + 1); 
          return new Report(report.getPrint() + report.getPrint(), false);
        } catch (Exception e) {
          return new Report("Ez nem is szám more. Retry: ", false);
        } 
      case 1:
        words = input.split(" ");
        if (words[0].equals(""))
          return new Report("Há, azé írhatná be valamit...\n", false); 
        if (words[0].equalsIgnoreCase("exit"))
          System.exit(0); 
        if (this.data.getCommands().get(words[0].toLowerCase()) == null)
          return new Report("Ilyen parancs nincs is bruh!\n", false); 
        commandReport = ((Command)this.data.getCommands().get(words[0].toLowerCase())).execute(words, this.data);
        if (commandReport.getCode())
          return commandReport; 
        temp = this.tracker.track(this.data);
        if (temp != null) {
          this.state = (byte)(this.state + 1);
          return new Report(commandReport.getPrint().concat(temp), false);
        } 
        return new Report(commandReport.getPrint().concat("\nPlayer " + (this.data.getPlayerMarker() ? "2" : "1") + " parancsa:\n"), false);
      case 2:
        System.exit(0);
        break;
    } 
    return new Report("", false);
  }
}
