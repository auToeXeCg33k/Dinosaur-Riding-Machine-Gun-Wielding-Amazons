package commands;

import core.World;

public class End implements Command {
  public void execute(String[] strs, World world) {
    world.turn();
  }
}
