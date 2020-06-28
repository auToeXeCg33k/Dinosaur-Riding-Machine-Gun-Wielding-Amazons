package commands;

import core.Data;

public class End implements Command {
  public String execute(String[] strs, Data data) {
    return "\n--- End of turn----\n";
  }
}
