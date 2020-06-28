package commands;

import core.World;

public interface Command {
  void execute(String[] paramArrayOfString, World paramWorld);
}
