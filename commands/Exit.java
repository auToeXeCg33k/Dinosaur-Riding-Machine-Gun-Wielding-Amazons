package commands;

import core.Data;

public class Exit implements Command {
  public String execute(String[] strs, Data data) {
    System.exit(0);
    return "Exiting.";
  }
}
