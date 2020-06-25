class Exit implements Command {
  public void execute(String[] strs, World world) {}
  
  public boolean execute() {
    System.out.println("jóvan jóvan lépek má");
    return false;
  }
}
