from rich.console import Console
from rich.panel import Panel
from rich.table import Table

console = Console()

def show_usage():
    """Display usage information"""
    console.print("[bold red]Usage:[/bold red]")
    console.print("  [cyan]usaco run random [-o][/cyan]   - Open random problem (add -o to open in browser)")
    console.print("  [cyan]usaco run <url> [-o][/cyan]    - Open specific problem (add -o to open in browser)")
    console.print("  [cyan]usaco list[/cyan]              - Show current problem")

def display_problem_card(problem, test_cases=None):
    """Display a nicely formatted card with problem details using Rich."""
    source = problem.get("source", {})
    title = problem.get("title", {})

    # Extract problem details
    problem_name = title.get("name", "Unknown Problem")
    problem_id = problem.get("id", "N/A")
    year = source.get("year", "N/A")
    contest = source.get("contest", "N/A")
    division = source.get("division", "N/A")
    place = title.get("place", "N/A")
    url = problem.get("url", "N/A")
    input_file = problem.get("input", "N/A")
    output_file = problem.get("output", "N/A")

    # Create the problem card
    table = Table(show_header=False, box=None, padding=(0, 1))
    table.add_column("Field", style="bold cyan")
    table.add_column("Value", style="white")

    table.add_row("Problem", f"[bold green]{problem_name}[/bold green]")
    table.add_row("ID", str(problem_id))
    table.add_row("Contest", f"{contest} {year}")
    table.add_row("Division", division.title())
    table.add_row("Position", f"Problem {place}")
    table.add_row("Input", input_file)
    table.add_row("Output", output_file)
    table.add_row("URL", f"[link]{url}[/link]")
    
    if test_cases is not None:
        table.add_row("Test Cases", str(test_cases))

    # Create panel with the table
    panel = Panel(
        table,
        title="[bold blue]🏆 USACO Problem[/bold blue]",
        border_style="blue",
        padding=(1, 2)
    )

    console.print()
    console.print(panel)
    console.print()

def print_success(message):
    """Print a success message"""
    console.print(f"[green]✓ {message}[/green]")

def print_error(message):
    """Print an error message"""
    console.print(f"[red]{message}[/red]")

def print_warning(message):
    """Print a warning message"""
    console.print(f"[yellow]{message}[/yellow]")

def print_info(message):
    """Print an info message"""
    console.print(f"[dim]{message}[/dim]")