import { Head } from "$fresh/runtime.ts";

export default function Home() {
  return (
    <>
      <Head>
        <title>Monitor de Sensores de trafico</title>
      </Head>
      <div class="p-4 mx-auto max-w-screen-md">
      </div>
      <footer class="bg-black grid grid-cols-2">
        <img
          src="/logo.svg"
          class="w-16 h-16"
          alt="the fresh logo: a sliced lemon dripping with juice"
        />
        <p class="my-6 text-white">
          Funcionando gracias a "fresh"
        </p>
      </footer>
    </>
  );
}
