\ProvidesClass{presentation}[2015/10/12 M. T. McCarthy Presentation Template]

\DeclareOption*{\PassOptionsToClass{\CurrentOption}{beamer}}
\ProcessOptions \relax

\LoadClass{beamer}

\RequirePackage{amsfonts}
\RequirePackage{amsmath}
\RequirePackage{amssymb}
\RequirePackage{amsthm}
\RequirePackage{graphicx}
\RequirePackage{hyperref}
\RequirePackage{mathtools}
\RequirePackage{setspace}
\RequirePackage{url}

\setbeamertemplate{theorems}[numbered]

\theoremstyle{plain}
\newtheorem{thm}{Theorem}[section]
\newtheorem{cor}[thm]{Corollary}
\newtheorem{lem}[thm]{Lemma}
\newtheorem{exmp}[thm]{Example}

\theoremstyle{definition}
\newtheorem{defn}{Definition}[section]

\def\AA{\mathbb{A}}	% Algebraics
\def\CC{\mathbb{C}}	% Complex
\def\FF{\mathbb{F}}	% Arbitrary field
\def\HH{\mathbb{H}}	% Quaternions
\def\KK{\mathbb{K}}	% Arbitrary field
\def\NN{\mathbb{N}}	% Naturals
\def\QQ{\mathbb{Q}}	% Rationals
\def\RR{\mathbb{R}}	% Reals
\def\ZZ{\mathbb{Z}}	% Integers

\renewcommand\Re{\operatorname{Re}}	% Real part of complex number
\renewcommand\Im{\operatorname{Im}}	% Imaginary part of complex number
\newcommand{\charec}{\operatorname{char}}

\newcommand{\ceil}[1]{\lceil #1 \rceil}
\newcommand{\floor}[1]{\lfloor #1 \rfloor}
\newcommand{\set}[1]{\lbrace #1 \rbrace}
\newcommand{\paren}[1]{\left( #1 \right)}
\newcommand{\brac}[1]{\left[ #1 \right]}
\newcommand{\angl}[1]{\langle #1 \rangle}
\newcommand{\abs}[1]{\left| #1 \right|}
% A matrix macro, all arguments are passed to the array environment
\newcommand{\mat}[2]
{
	\brac{
		\begin{array}{ #1 }
			#2
		\end{array}
	}
}
% A determinant macro, all arguments are passed to the array environment
\newcommand{\deter}[2]
{
	\abs{
	\	begin{array}{ #1 }
			#2
		\end{array}
	}
}
