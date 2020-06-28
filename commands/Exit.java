package commands;

import core.World;

public class Exit implements Command {
  public void execute(String[] strs, World world) {
    System.exit(0);
  }
}
