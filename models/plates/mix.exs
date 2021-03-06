defmodule Plates.MixProject do
  use Mix.Project

  def project do
    [
      app: :plates,
      version: "0.1.0",
      elixir: "~> 1.7",
      start_permanent: Mix.env() == :prod,
      deps: deps()
    ]
  end

  # Run "mix help compile.app" to learn about applications.
  def application do
    [
      extra_applications: [:logger]
    ]
  end

  # Run "mix help deps" to learn about dependencies.
  defp deps do
    [
      # {:dep_from_hexpm, "~> 0.3.0"},
      {:dep_from_git, git: "https://github.com/NatTuck/laser_path.git", app: false},
    ]
  end
end
