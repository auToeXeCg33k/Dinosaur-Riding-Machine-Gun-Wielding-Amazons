package core;

public class inputHandler {
  private Data data = new Data();
  
  private Tracker tracker = new Tracker();
  
  private byte state = 0;
  
  public String handle(Window window) {
    String splitInput[], ret, temp, input = window.getInput();
    switch (this.state) {
      case 0:
        try {
          byte b = Byte.parseByte(input);
          if (b >= 1 && b <= 1) {
            this.state = 1;
            return this.data.createWorld(b) + "\nPlayer 1 parancsa:\n";
          } 
          return "Ilyen játékmód nincs. Retry: ";
        } catch (Exception e) {
          if (input.equalsIgnoreCase("exit"))
            System.exit(0); 
          return "Ilyen játékmód nincs. Retry: ";
        } 
      case 1:
        splitInput = input.split(" ");
        if (splitInput[0].equals(""))
          return "Há, azé írhatná be valamit...\n"; 
        if (this.data.getCommand(splitInput[0].toLowerCase()) == null)
          return "Ilyen parancs nincs is bruh!\n"; 
        if (splitInput[0].equalsIgnoreCase("end")) {
          window.println(this.data.getCommand("end").execute(splitInput, this.data));
          this.data.turn();
          window.changeWindow(this.data.getPlayerMarker());
          return "Player " + (this.data.getPlayerMarker() ? "2" : "1") + " parancsa:\n";
        } 
        ret = this.data.getCommand(splitInput[0].toLowerCase()).execute(splitInput, this.data).concat("\nPlayer " + (this.data.getPlayerMarker() ? "2" : "1") + " parancsa:\n");
        temp = this.tracker.track(this.data);
        if (!temp.equalsIgnoreCase("")) {
          this.state = 2;
          return ret.concat(temp);
        } 
        return ret;
      case 2:
        System.exit(0);
        return "";
    } 
    return "";
  }
}
