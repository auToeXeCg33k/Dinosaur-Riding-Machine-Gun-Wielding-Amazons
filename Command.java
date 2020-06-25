public interface Command {
  void execute(String[] paramArrayOfString, World paramWorld);
  
  boolean execute();
}
